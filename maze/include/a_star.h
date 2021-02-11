#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>
#include <memory>

namespace ecn
{

// compare nodes
template <class Node>
inline bool areSame(const Node * l1, const Node * l2)
{
    return *l1 == *l2;
}
template <class Node>
inline bool areSame(const Node * l1, const Node & l2)
{
    return *l1 == l2;
}

// a custom map for unique ptr's
template <class Node>
class PtrMap : std::vector<std::pair<std::unique_ptr<Node>, Node*>>
{
public:
    void write(Node* key, Node* val)
    {
        // usually we find it near the end
        for(auto v = this->rbegin(); v != this->rend(); v++)
        {
            if(v->first.get() == key)
            {
                v->second = val;
                return;
            }
        }
    }

    Node* get(Node* key)
    {
        // usually we find it near the end
        for(auto v = this->rbegin(); v != this->rend(); v++)
        {
            if(v->first.get() == key)
            {
                return v->second;
            }
        }
        return 0;
    }

    // insertion
    void add(std::unique_ptr<Node> &key, Node* val)
    {
        this->push_back({std::move(key), val});
    }
};

// reconstruct path from last best element
template<class Node>
void reconstructPath(PtrMap<Node> &come_from, Node* best, int dist)
{
    std::vector<Node*> summary = {best};
    // build list from end to start
    while(come_from.get(best))
    {
        best = come_from.get(best);
        summary.push_back(best);
    }
    // list from start to end
    std::reverse(summary.begin(),summary.end());

    for(auto &elem: summary)
    {
        if(come_from.get(elem))
            elem->print(*come_from.get(elem));
    }
    std::cout << "solved in " << summary.size()-1 << " steps, distance is " <<
                 dist << std::endl;
}

// templated version of A* algorithm
template<class Node>
void Astar(Node start, Node goal)
{
    // check if we should display during A*
    std::ifstream config("../config.txt", std::ios::in);
    std::string keyword;
    bool show = false, use_manhattan = true;
    while(config >> keyword)
    {
        if(keyword == "show")
            config >> show;
        else if(keyword == "use_manhattan")
            config >> use_manhattan;
        else
        {
            std::string dummy;
            config >> dummy;
        }
    }

    auto t0 = std::chrono::system_clock::now();

    typedef std::unique_ptr<Node> Tptr;

    struct NodeWithCost
    {
        Node* elem;
        double f;
        int g;
    };
    struct Compare
    {
        bool operator()(const NodeWithCost& a, const NodeWithCost& b)
        {
            if(a.f == b.f)
                return a.g < b.g;
            return a.f > b.f;
        }
    };

    class priority_access :
            public std::priority_queue<NodeWithCost, std::vector<NodeWithCost>, Compare>
    {
    public:
        NodeWithCost* find( const Node& node)
        {
            // when looking for an given element,
            // the best occurrence should be near the end
            for(auto it = this->c.rbegin(); it!=this->c.rend(); it++)
            {
                if(areSame(it->elem,node))
                    return &(*it);
            }
            return 0;
        }
    };

    std::vector<Node*> closedSet;
    priority_access queue;
    queue.push({&start, start.h(goal, use_manhattan), 0});

    // keep track of who comes from who
    PtrMap<Node> come_from;

    if(show)
        start.start();

    int evaluated = 0, created = 0, shortcut = 0;
    evaluated++;
    while(!queue.empty())
    {
        auto best = queue.top();

        if(areSame(best.elem,goal))
        {
            std::cout << created << " nodes created, " <<
                         evaluated << " evaluated, " <<
                         shortcut << " shortcuts found" << std::endl;
            std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>
                         (std::chrono::system_clock::now()-t0).count() << " ms" << std::endl;
            reconstructPath(come_from, best.elem, best.g);
            return;
        }

        closedSet.push_back(best.elem);
        queue.pop();
        if(show)
        {
            Node* parent = come_from.get(best.elem);
            if(parent)
                best.elem->show(true, *parent);
        }


        auto children = best.elem->children();
        created += children.size();

        // to avoid equal costs leading to favorite directions
        std::random_shuffle(children.begin(), children.end());

        for(auto &child: children)
        {
            auto child_ptr = child.get();
            // ensure we have not been here
            if(std::find_if(closedSet.rbegin(), closedSet.rend(),
                            [&child_ptr](Node* elem){return areSame(elem,child_ptr);}) == closedSet.rend())
            {
                auto twin = queue.find(*child_ptr);
                const int child_g = best.g + child_ptr->distToParent();
                if(!twin)
                {
                    queue.push({child_ptr,
                                child_ptr->h(goal, use_manhattan) + child_g,
                                child_g});
                    evaluated++;
                    come_from.add(child, best.elem);
                    if(show)
                        child_ptr->show(false, *best.elem);
                }
                else if(twin->g > child_g)
                {
                    come_from.write(twin->elem, best.elem);
                    queue.push({twin->elem, twin->f - twin->g + child_g, child_g});
                    shortcut++;
                }
            }
        }
    }

    // while loop exit means no solutions
    std::cout << "No solutions " << std::endl;
    std::cout << created << " nodes created, " <<
                 evaluated << " evaluated, " <<
                 shortcut << " shortcuts found" << std::endl;
}

}

#endif // A_STAR_H

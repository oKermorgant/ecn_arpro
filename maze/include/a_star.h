#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>

namespace ecn
{

// anonymous namespace for implementation details
namespace
{
// compare pointer and object
template <class Node>
inline bool areSame(const Node * l1, const Node & l2)
{
    return *l1 == l2;
}

// resulting tree + owner of objects
template <class Node>
class Tree : public std::map<Node*, Node*>
{
    std::queue<std::unique_ptr<Node>> nodes;
    std::vector<Node*> closedSet;
public:
    inline void insert(std::unique_ptr<Node> & node, Node* parent)
    {
        std::map<Node*, Node*>::emplace(node.get(), parent);
        nodes.emplace(std::move(node));
    }
    inline void close(Node * node)
    {
        closedSet.push_back(node);
    }
    inline bool isVisited(Node * node_ptr) const
    {
        const auto &node(*node_ptr);
        return std::find_if(closedSet.rbegin(), closedSet.rend(),[&node](Node* elem)
        {return areSame(elem, node);}) != closedSet.rend();
    }
    std::vector<Node> fullPathTo(Node* best, int dist) const
    {
        std::vector<Node> path;
        const auto start(closedSet[0]);
        // build list from end to start
        while(best != start)
        {
            path.push_back(*best);
            best = this->at(best);
        }
        path.push_back(*start);
        // list from start to end
        std::reverse(path.begin(),path.end());
        for(size_t i = 1; i < path.size(); ++i)
            path[i-1].print(path[i]);

        std::cout << "solved in " << path.size()-1 << " steps, distance is " << dist << std::endl;

        return path;
    }
};

// Generic node with distance to start (g) + total cost from heuristic (f = g+h)
template <class Node>
struct NodeWithCost
{
    Node* node;
    double f;
    double g;
    inline NodeWithCost(Node* _node=nullptr, double _h=0, double _g=0)
        : node(_node), f(_h+_g), g(_g) {}
    bool operator<(const NodeWithCost & other) const
    {
        // if(f == other.f)
        //   return g < other.g;
        return f >= other.f;
    }
};

// Priory queue with find
template <class Node>
class Queue :
        public std::priority_queue<NodeWithCost<Node>, std::vector<NodeWithCost<Node>>>
{
public:
    std::pair<NodeWithCost<Node>,bool> find(const Node& node)
    {
        for(auto &it : this->c)
        {
            if(areSame(it.node, node))
                return {it,true};
        }
        return {{},false};
    }
};
}


// templated version of A* algorithm
template<class Node>
std::vector<Node> Astar(Node start, Node goal)
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

    Queue<Node> queue;
    queue.push({&start, start.h(goal, use_manhattan), 0});

    // keep track of who comes from who
    Tree<Node> tree;

    if(show)
        start.start();

    int evaluated = 0, created = 0, shortcut = 0;
    evaluated++;
    while(!queue.empty())
    {
        auto best = queue.top();

        if(areSame(best.node,goal))
        {
            std::cout << created << " nodes created, " <<
                         evaluated << " evaluated, " <<
                         shortcut << " shortcuts found" << std::endl;
            std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>
                         (std::chrono::system_clock::now()-t0).count() << " ms" << std::endl;

            return tree.fullPathTo(best.node, best.g);
        }

        tree.close(best.node);
        queue.pop();
        if(show)
        {
            Node* parent = tree[best.node];
            if(parent)
                best.node->show(true, *parent);
        }

        auto children = best.node->children();
        created += children.size();

        // to avoid equal costs leading to favorite directions
        std::random_shuffle(children.begin(), children.end());

        for(auto &child: children)
        {
            // ensure we have not been here
            if(auto child_ptr(child.get()); !tree.isVisited(child_ptr))
            {
                const auto child_g = best.g + child_ptr->distToParent();
                if(const auto &[twin,valid] = queue.find(*child_ptr); !valid)
                {
                    queue.push({child_ptr,
                                child_ptr->h(goal, use_manhattan) + child_g,
                                child_g});
                    evaluated++;
                    tree.insert(child, best.node);
                    if(show)
                        child_ptr->show(false, *best.node);
                }
                else if(twin.g > child_g)
                {
                    tree[twin.node] = best.node;
                    queue.push({twin.node, twin.f - twin.g + child_g, child_g});
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
    return {};
}

}

#endif // A_STAR_H

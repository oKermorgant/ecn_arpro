#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <chrono>

namespace ecn
{

// reconstruct path from last best element
template<class T>
void reconstructPath(std::unordered_map<T*, T*> &come_from, T* best, int dist)
{
    std::vector<T*> summary = {best};
    // build list from end to start
    while(come_from[best])
    {
        best = come_from[best];
        summary.push_back(best);
    }
    // list from start to end
    std::reverse(summary.begin(),summary.end());

    for(auto &elem: summary)
        elem->print(come_from[elem]);
    std::cout << "Need " << dist << " moves" << std::endl;
}


// templated version of A* algorithm
template<class T>
void Astar(T start, T goal)
{
    auto t0 = std::chrono::system_clock::now();

    struct NodeWithCost
    {
        T* elem;
        int f;
        int g;
    };
    struct Compare
    {
        bool operator()(const NodeWithCost& a, const NodeWithCost& b)
        {
            // if(a.f == b.f)
            //     return a.g < b.g;
            return a.f > b.f;
        }
    };

    class priority_access :
            public std::priority_queue<NodeWithCost, std::vector<NodeWithCost>, Compare>
    {
    public:
        NodeWithCost* find(T* elem)
        {
            // when looking for an given element,
            // the best occurrence should be near the end
            for(auto it = this->c.rbegin(); it!=this->c.rend(); it++)
            {
                if(it->elem->is(elem))
                    return &(*it);
            }
            return 0;
        }
    };


    std::vector<T*> closedSet;
    std::vector<T*> children;
    priority_access queue;
    queue.push({&start, start.h(goal), 0});

    // keep track of who comes from who
    std::unordered_map<T*, T*> come_from = {{&start, 0}};

    int evaluated = 0, created = 0, shortcut = 0;
    evaluated++;
    while(!queue.empty())
    {
        auto best = queue.top();

        if(best.elem->is(&goal))
        {

            reconstructPath(come_from, best.elem, best.g);
            std::cout << created << " nodes created, " <<
                         evaluated << " evaluated, " <<
                         shortcut << " shortcuts found" << std::endl;
            std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>
                         (std::chrono::system_clock::now()-t0).count() << " ms" << std::endl;
            return;
        }

        closedSet.push_back(best.elem);
        queue.pop();

        best.elem->children(children);
        created += children.size();

        // to avoid equal costs leading to favorite directions
        std::random_shuffle(children.begin(), children.end());

        for(auto child: children)
        {
            // ensure we have not been here
            if(std::find_if(closedSet.rbegin(), closedSet.rend(),
                            [child](T* elem){return elem->is(child);}) == closedSet.rend())
            {
                auto twin = queue.find(child);
                const int child_g = best.g + child->distToParent();
                if(!twin)
                {
                    queue.push({child, child->h(goal) + child_g, child_g});
                    evaluated++;
                    come_from[child] = best.elem;
                }
                else
                {
                    if(twin->g > child_g)
                    {
                        come_from[twin->elem] = best.elem;
                        queue.push({twin->elem, twin->f - twin->g + child_g, child_g});
                        shortcut++;
                    }
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

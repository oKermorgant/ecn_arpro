#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <chrono>
#include <memory>

namespace ecn
{

// a custom map for unique ptr's
template <class T>
class PtrMap : std::vector<std::pair<std::unique_ptr<T>, T*>>
{
public:
  void write(T* key, T* val)
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

  T* get(T* key)
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

  // when called with a Tptr, we want to insert
  void add(std::unique_ptr<T> &key, T* val)
  {
    this->push_back({std::move(key), val});
  }
};


// reconstruct path from last best element
template<class T>
void reconstructPath(PtrMap<T> &come_from, T* best, int dist)
{
  std::vector<T*> summary = {best};
  // build list from end to start
  while(come_from.get(best))
  {
    best = come_from.get(best);
    summary.push_back(best);
  }
  // list from start to end
  std::reverse(summary.begin(),summary.end());

  for(auto &elem: summary)
    elem->print(come_from.get(elem));
  std::cout << "solved in " << summary.size()-1 << " steps, distance is " <<
               dist << std::endl;
}

// templated version of A* algorithm
template<class T>
void Astar(T start, T goal)
{
  auto t0 = std::chrono::system_clock::now();

  struct NodeWithCost
  {
    T* elem;
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
    NodeWithCost* find( const T& elem)
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
  priority_access queue;
  queue.push({&start, start.h(goal), 0});

  // keep track of who comes from who
  PtrMap<T> come_from;

  int evaluated = 0, created = 0, shortcut = 0;
  evaluated++;
  while(!queue.empty())
  {
    auto best = queue.top();

    if(best.elem->is(goal))
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

    auto children = best.elem->children();
    created += children.size();

    // to avoid equal costs leading to favorite directions
    std::random_shuffle(children.begin(), children.end());

    for(auto &child: children)
    {
      auto child_ptr = child.get();
      // ensure we have not been here
      if(std::find_if(closedSet.rbegin(), closedSet.rend(),
                      [&child_ptr](T* elem){return elem->is(*child_ptr);}) == closedSet.rend())
      {
        auto twin = queue.find(*child_ptr);
        const int child_g = best.g + child_ptr->distToParent();
        if(!twin)
        {
          queue.push({child_ptr,
                      child_ptr->h(goal) + child_g,
                      child_g});
          evaluated++;
          come_from.add(child, best.elem);
        }
        else
        {
          if(twin->g > child_g)
          {
            come_from.write(twin->elem, best.elem);
            queue.push({twin->elem, twin->f - twin->g + child_g, child_g});
            shortcut++;
          }
        }
      }
    }
  }

  std::cout << "No solutions " << std::endl;
  std::cout << created << " nodes created, " <<
               evaluated << " evaluated, " <<
               shortcut << " shortcuts found" << std::endl;
}

}

#endif // A_STAR_H

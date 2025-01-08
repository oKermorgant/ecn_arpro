#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
#include <chrono>

namespace ecn
{

// namespace for implementation details
namespace astar_impl
{

// resulting tree + owner of objects

template <class State>
class Tree
{
  struct NodeWithCost
  {
    size_t idx;
    int f;
    int g;
    inline NodeWithCost(size_t idx, int h=0, int g=0)
        : idx{idx}, f{h+g}, g{g} {}
    bool operator<(const NodeWithCost & other) const
    {
      return f >= other.f;
    }
  };

  std::vector<State> nodes;
  std::vector<size_t> parents;
  std::vector<size_t> closedSet;
  std::vector<NodeWithCost> queue;

  void push(const NodeWithCost &node)
  {
    queue.push_back(node);
    std::push_heap(queue.begin(), queue.end());
  }

public:

  explicit Tree(State start, int h)
  {
    insert(std::move(start), 0, h, 0);
  }

  inline void insert(State &&state, size_t parent, int h, int g)
  {
    nodes.emplace_back(std::forward<State>(state));
    parents.push_back(parent);
    push({nodes.size()-1, h, g});
  }

  inline bool hasFrontier() const {return !queue.empty();}

  std::optional<NodeWithCost> find(const State& state) const
  {
    if(const auto same{std::find_if(queue.rbegin(), queue.rend(),
                                 [&](const auto &twin)
                                     {return nodes[twin.idx] == state;})};
        same != queue.rend())
      return *same;
    return {};
  }

  inline NodeWithCost best()
  {
    std::pop_heap(queue.begin(), queue.end());
    const auto ret{queue.back()};
    queue.pop_back();
    closedSet.push_back(ret.idx);
    return ret;
  }

  inline const State& operator()(const NodeWithCost &node) const
  {
    return nodes[node.idx];
  }

  inline void setParent(const NodeWithCost &node, size_t parent, int g)
  {
    push({node.idx, node.f-node.g, g});
    parents[node.idx] = parent;
  }

  inline bool isVisited(const State &state) const
  {
    return std::find_if(closedSet.rbegin(), closedSet.rend(),[&](const auto idx)
                        {return nodes[idx] == state;}) != closedSet.rend();
  }
  std::vector<State> fullPathTo(const NodeWithCost &node) const
  {
    auto last_idx{node.idx};

    std::vector<State> path;
    // build list from end to start
    while(last_idx)
    {            
      path.push_back(nodes[last_idx]);
      last_idx = parents[last_idx];
    }
    path.push_back(nodes[0]);
    // list from start to end
    std::reverse(path.begin(),path.end());
    for(size_t i = 1; i < path.size(); ++i)
      path[i-1].print(path[i]);

    std::cout << "solved in " << path.size()-1 << " steps, distance is " << node.g << std::endl;

    return path;
  }
};
}


// templated version of A* algorithm
template<class Node>
std::vector<Node> Astar(const Node &start, const Node &goal)
{
  auto t0 = std::chrono::system_clock::now();

  // keep track of who comes from who
  astar_impl::Tree<Node> tree(start, start.h(goal));

  int evaluated = 0, created = 0, shortcut = 0;
  evaluated++;
  while(tree.hasFrontier())
  {
    const auto best{tree.best()};

    if(tree(best) == goal)
    {
      std::cout << created << " nodes created, " <<
          evaluated << " evaluated, " <<
          shortcut << " shortcuts found" << std::endl;
      std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>
                               (std::chrono::system_clock::now()-t0).count() << " ms" << std::endl;

      return tree.fullPathTo(best);
    }

    auto children{tree(best).children()};
    created += children.size();

    // to avoid equal costs leading to favorite directions
    //std::random_shuffle(children.begin(), children.end());

    for(auto &&child: children)
    {
      // ensure we have not been here
      if(tree.isVisited(child))
        continue;

      const auto child_g = best.g + child.distToParent();
      if(const auto &twin{tree.find(child)}; !twin)
      {
        tree.insert(std::move(child), best.idx, child.h(goal), child_g);
        evaluated++;
      }
      else if(twin->g > child_g)
      {
        tree.setParent(*twin, best.idx, child_g);
        shortcut++;
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

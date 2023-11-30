#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <algorithm>

struct Node
{
  static inline uint count = 0;
  uint id;

  std::vector<Node> neighboors; // bad idea, neighboors would be copies

  Node() : id(count++) {}
};


struct Graph
{
private:
  using NodePtr = std::unique_ptr<Node>;
  using Neighboors = std::vector<Node*>;
  std::unordered_map<NodePtr, Neighboors> nodes;

public:

  auto find(uint id)
  {
    return std::find_if(nodes.begin(), nodes.end(), [id](const auto &node)
    {
      return node.first->id == id;
    })->first.get();
  }

  void add(const Node &node)
  {

  }
  void add()
  {

  }

  void addEdge(uint id1, uint id2)
  {
    auto node1 = find(id1);
    auto node2 = find(id2);

  }

  void print()
  {
    for(const auto &[node, nb]: nodes)
    {
      std::cout << " - " << node->id << " : [";
      for(auto &other: nb)
        std::cout << other->id << " ";
      std::cout << "]\n";
    }
    std::cout << '\n';
  }
};



int main()
{

}

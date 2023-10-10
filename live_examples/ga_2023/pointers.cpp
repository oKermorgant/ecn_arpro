#include <iostream>
#include <vector>
#include <memory>
struct Node
{
  int x, y;
  Node* parent;

  Node(int x, int y, Node* parent = nullptr)
    : x{x}, y{y}, parent{parent}
  {
  }

  void print()
  {
    std::cout << "(" << x << ", " << y << ") ";
    if(parent)
      std::cout << " my parent is @ (" << parent->x
              << ", " << parent->y << ")";
    std::cout << '\n';
  }


};




int main()
{
  Node node1(1, 2);
  Node node2(3,4, &node1);

  std::vector<std::unique_ptr<Node>> tree;
  tree.reserve(4);
  tree.emplace_back(std::make_unique<Node>(1,2));
  for(int i = 0; i < 8; ++i)
  {
    tree.emplace_back(std::make_unique<Node>(i,i,
                                             tree[i / 2].get()));
  }

  for(auto &node: tree)
    node->print();







}

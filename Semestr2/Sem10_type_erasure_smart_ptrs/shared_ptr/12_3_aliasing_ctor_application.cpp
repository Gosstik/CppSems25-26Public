#include <iostream>
#include <memory>

template <typename Data>
class Tree {
  private:
    struct Node {
        std::shared_ptr<Node> left, right;
        Data d;
    };

  public:
    std::shared_ptr<Data> Find(int inorder_pos) {
        std::shared_ptr<Node> spn;
        // search and put result to spn
        return {spn, &(spn->d)};
    }

  private:
    std::shared_ptr<Data> top_;
};

#include <iostream>

template <typename Key, typename Value, typename Compare = std::less<Key>>
class Map {
    //  struct Node {
    //    std::pair<Key, Value> kv;
    //    Node* left;
    //    Node* right;
    //    Node* parent; // for iterator
    //    bool red;
    //  };

    struct BaseNode {
        BaseNode* left;
        BaseNode* right;
        BaseNode* parent;  // for iterator
    };

    struct Node : BaseNode {
        std::pair<const Key, Value> kv;
        bool red;
    };

    BaseNode fake_node_;
    BaseNode* first_;
    size_t size_;
    Compare cmp_;
};

int main() {}

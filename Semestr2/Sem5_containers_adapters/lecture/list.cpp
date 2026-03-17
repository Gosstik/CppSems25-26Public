#include <iostream>

template <typename T>
class List {
    struct BaseNode {
        BaseNode* prev;
        BaseNode* next;
    };

    struct Node : BaseNode {
        T value;
    };

    BaseNode head;
    // Node* tail;
    size_t size_;

  public:
    List() : head(&head, &head) {}  // NOLINT
};

int main() {}

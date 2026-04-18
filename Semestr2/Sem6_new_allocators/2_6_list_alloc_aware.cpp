#include <cstddef>
#include <memory>

// rebind

template <typename T, typename TAlloc = std::allocator<T>>
class List {
  private:
    struct BaseNode {
        BaseNode* prev;
        BaseNode* next;
    };
    struct Node : BaseNode {
        T value;
    };

    // !!! no rebind in std::allocator_traits
    // !!! instead it has rebind_alloc and rebind_traits
    using TAllocTraits = std::allocator_traits<TAlloc>;
    // same as allocator::rebind
    using NodeAlloc = typename TAllocTraits::template rebind_alloc<Node>;
    using NodeAllocTraits = typename TAllocTraits::template rebind_traits<Node>;

    BaseNode head_;
    size_t size_;
    // !!! CE: no rebind in std::allocator
    // typename Alloc::template rebind<Node>::other alloc_;
    NodeAllocTraits alloc_; // !!! We store NodeAlloc, not TAlloc

  public:
    List() = default;

    explicit List(const TAlloc& alloc)
        : head_{&head_, &head_},
          size_(0),
          alloc_(alloc) {}
};

int main() { List<int> l; }

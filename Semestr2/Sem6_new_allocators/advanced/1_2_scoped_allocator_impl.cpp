#include <iostream>
#include <memory>  // uses_allocator
#include <scoped_allocator>
#include <string>
#include <vector>

////////////////////////////////////////////////////

// Live coding

template <typename Alloc>
struct scoped_allocator_adaptor {
  public:
    // ... allocate(), deallocate(), usings ...

    template <typename T, typename... Args>
    void construct(T* ptr, const Args&... args) {
        // https://en.cppreference.com/w/cpp/memory/uses_allocator
        if constexpr (std::uses_allocator_v<T, Alloc>) {
            using InnerAlloc = typename T::allocator_type;
            // Actually scoped_allocator_adaptor is passed.
            // scoped_allocator_adaptor inherits Alloc.
            alloc.construct(ptr, args..., InnerAlloc(alloc));
        } else {
            alloc.construct(ptr, args...);
        }
    }

  private:
    Alloc alloc;
};

////////////////////////////////////////////////////

template <typename T>
using MyAlloc = std::allocator<T>;

int main() {
    using MyString =
        std::basic_string<char, std::char_traits<char>, MyAlloc<char>>;

    MyAlloc<MyString> alloc;

    std::vector<MyString, MyAlloc<MyString>> v(alloc);
    // std::vector<MyString, std::scoped_allocator_adaptor<MyAlloc<MyString>>> v(
    //     alloc);

    v.push_back("abc");
    v.push_back("ced");
}



// use uninitialized_move and move_if_noexcept
// Rule of five

// delete before moving !!!

// S(const string& data): data(data) {}
// S(string&& data): data(std::move(data)) {} // ! missing std::move causes copy

// operator=(vector&&) can work O(n) if iterators are not equal
// and pocma == false

// Move ctor must be marked noexcept !!!
// See impl of std::move_if_noexcept (declaration is already an impl :) )
// Why do we need condition std::is_copy_constructible ???

// std::vector<std::string> v(5, "abc");
// v.push_back(v[3]);

#include <memory>  // std::allocator, std::allocator_traits
#include <utility>
#include <vector>

template <typename T, typename Alloc = std::allocator<T>>
class Vector {
  private:
    using AllocTraits = std::allocator_traits<Alloc>;

  public:
    void Reserve(size_t) {
        // impl ...
    }

    void EmplaceBack(auto&&... args) {
        if (size_ == cap_) {
            Reserve(cap_ > 0 ? cap_ * 2 : 4);
        }
        AllocTraits::construct(
            alloc_,
            arr_ + size_,
            std::forward<decltype(args)>(args)...  // && + &&
        );
        ++size_;
    }

    // template <typename... Args>
    // void EmplaceBack2(Args&&... args) {
    //     if (size_ == cap_) {
    //         Reserve(cap_ > 0 ? cap_ * 2 : 4);
    //     }
    //     AllocTraits::construct(
    //         alloc_,
    //         arr_ + size_,
    //         std::forward<Args>(args)...  // no && + &&
    //     );
    //     ++size_;
    // }

    void PushBack(const T& value) { EmplaceBack(value); }

    void PushBack(T&& value) { EmplaceBack(std::move(value)); }

  private:
    T* arr_;
    size_t size_;
    size_t cap_;
    [[no_unique_address]] Alloc alloc_;
};

////////////////////////////////////////////

int main() { std::vector<int> vec; }

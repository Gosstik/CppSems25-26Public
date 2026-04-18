

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
    void Reserve(size_t newcap) {
        if (newcap <= cap_) {
            return;
        }

        // T* newarr = reinterpret_cast<T*>(new char[newcap * sizeof(T)]);
        // T* newarr = alloc_.allocate(newcap);
        T* newarr = AllocTraits::allocate(alloc_, newcap);
        size_t ind = 0;

        try {
            for (; ind < size_; ++ind) {
                // new (newarr + ind) T(arr_[ind]);  // placement new
                // alloc_.construct(newarr + ind, arr_[ind]);
                AllocTraits::construct(alloc_, newarr + ind, arr_[ind]);
            }
        } catch (...) {
            for (size_t old_ind = 0; old_ind < ind; ++old_ind) {
                // (newarr + ind)->~T();
                // alloc_.destroy(newarr + old_ind);
                AllocTraits::destroy(alloc_, newarr + old_ind);
            }
            // delete[] reinterpret_cast<char*>(newarr);
            // alloc_.deallocate(newarr, newcap);
            AllocTraits::deallocate(alloc_, newarr, newcap);
            throw;
        }

        for (ind = 0; ind < size_; ++ind) {
            // (arr_ + ind)->~T();
            AllocTraits::destroy(alloc_, newarr + ind);
        }
        // delete[] reinterpret_cast<char*>(arr_);
        AllocTraits::deallocate(alloc_, arr_, cap_);

        arr_ = newarr;
        cap_ = newcap;
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }

        // if constexpr
        Alloc newalloc =
            AllocTraits::propagate_on_container_copy_assignment::value
                ? other.alloc_
                : alloc_;

        // TODO: reconsider logic (memory must be freed by previous alloc)
        // TODO is_always_equal
        // TODO: how to copy alloc in case of EBO ???
        // TODO: reuse memory in case allocs are equal (no realloc if
        // sufficient)

        T* newarr = AllocTraits::allocate(alloc_, other.cap_);
        size_t i = 0;
        try {
            for (; i < other.size(); ++i) {
                AllocTraits::construct(
                    newalloc, newarr + i, std::move_if_noexcept(other[i]));
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                AllocTraits::destroy(newalloc, newarr + j);
            }
            AllocTraits::deallocate(newalloc, newarr, other.cap_);
            throw;
        }

        for (i = 0; i < size_; ++i) {
            AllocTraits::destroy(alloc_, arr_ + i);
        }
        AllocTraits::deallocate(alloc_, arr_, cap_);

        arr_ = newarr;
        size_ = other.size_;
        cap_ = other.cap_;
        alloc_ = newalloc;  // TODO if constexpr
    }

    // TODO: move ctor

    template <typename... Args>
    void EmplaceBack(Args&&... args) {
        if (size_ == cap_) {
            Reserve(cap_ > 0 ? cap_ * 2 : 4);
        }
        AllocTraits::construct(
            alloc_, arr_ + size_, std::forward<Args>(args)...);
        ++size_;
    }

    void PushBack(const T& value) { EmplaceBack(value); }

    void PushBack(T&& value) { EmplaceBack(std::move(value)); }

  private:
    T* arr_;
    size_t size_;
    size_t cap_;
    Alloc alloc_;  // TODO: change to EBO or [[no_unique_address]]
};

////////////////////////////////////////////

int main() {
    // TODO: Problem with our implementation
    std::vector<std::string> vec(5, "abc");
    vec.push_back(vec[3]);
}

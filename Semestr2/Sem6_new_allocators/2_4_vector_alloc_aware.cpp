#include <memory>  // std::allocator, std::allocator_traits
#include <vector>

template <typename T, typename Alloc = std::allocator<T>>
class Vector {
  private:
    using AllocTraits = std::allocator_traits<Alloc>;
    using allocator_type = Alloc;

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

        T* newarr = AllocTraits::allocate(newalloc, other.cap_);
        size_t i = 0;
        try {
            for (; i < other.size(); ++i) {
                AllocTraits::construct(newalloc, newarr + i, other[i]);
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

    // TODO: get_allocator (returns copy)

  private:
    T* arr_;
    size_t size_;
    size_t cap_;
    [[no_unique_address]] Alloc alloc_;  // TODO: change to EBO
};

////////////////////////////////////////////

int main() { std::vector<int> vec; }

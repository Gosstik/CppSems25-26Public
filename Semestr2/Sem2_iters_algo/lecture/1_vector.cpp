#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

// Implementation:
// /usr/include/c++/13/bits/stl_vector.h
// /usr/include/c++/13/bits/vector.tcc
// /usr/include/c++/13/bits/stl_bvector.h

template <typename T>
class Vector {
  public:
    void Reserve(size_t new_cap) {
        if (new_cap <= cap_) {
            return;
        }

        // T* new_arr = new T[new_cap]; // does not work for non-trivial types
        T* new_arr = reinterpret_cast<T*>(new char[new_cap * sizeof(T)]);
        size_t ind = 0;

        // try {
        //   std::uninitialized_copy(arr_, arr_ + size_, new_arr);
        // } catch (...) {
        //   delete[] reinterpret_cast<char*>(new_arr);
        //   throw;
        // }

        try {
            for (; ind < size_; ++ind) {
                /// UB (operator= on uninitialized memory)
                // new_arr[ind] = arr_[ind];

                /// memcpy: UB when T has fields that references to other fields
                /// (std::string for example)

                new (new_arr + ind) T(arr_[ind]);  // placement new
            }
        } catch (...) {
            for (size_t old_ind = 0; old_ind < ind; ++old_ind) {
                (new_arr + ind)->~T();
            }
            delete[] reinterpret_cast<char*>(new_arr);
            throw;
        }

        // delete[] arr_; // UB
        for (ind = 0; ind < size_; ++ind) {
            (arr_ + ind)->~T();
        }
        delete[] reinterpret_cast<char*>(arr_);

        arr_ = new_arr;
        cap_ = new_cap;
    }

    void PushBack(const T& value) {
        if (size_ == cap_) {
            // !!! Wrong in case placing value will cause exception
            Reserve(cap_ > 0 ? cap_ * 2 : 1);
        }

        // handle value
    }

  private:
    T* arr_;
    size_t size_;
    size_t cap_;
};

////////////////////////////////////////////

template <>
class Vector<bool> {
  private:
    struct BitReference {
        char* cell;
        uint8_t ind;  // in [0, 7]

        BitReference(char* cell, size_t ind) : cell(cell), ind(ind) {}

        BitReference operator=(bool b) {
            if (b) {
                *cell |= (1 << ind);
            } else {
                *cell &= ~(1 << ind);
            }
            return *this;
        }

        operator bool() const {  // NOLINT(google-explicit-constructor)
            return (*cell) & (1 << ind);
        }
    };

  public:
    BitReference operator[](size_t ind) { return {arr_ + ind / 8, ind % 8}; }

  private:
    char* arr_;
    size_t size_;
    size_t cap_;
};

template <typename T>
void Debug(T) = delete;

int main() {
    std::vector<bool> v(10);
    // Debug(v[5]);                // print type: T = std::_Bit_reference
    v[5] = true;                // assigning to rvalue
    std::cout << v[5] << '\n';  // why it works ???
}

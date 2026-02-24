#include <cstddef>

template <typename T>
class Vector {
  public:
    Vector() = default;

    void PushBack(const T& val) {
        // TODO
    }

  private:
    T* arr_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
};

int main() {}

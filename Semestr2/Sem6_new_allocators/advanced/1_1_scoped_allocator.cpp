#include <iostream>
#include <memory>
#include <scoped_allocator>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

void* operator new(size_t n) {
    std::cout << "new: " << n << " bytes allocated\n";
    return malloc(n);
}

void operator delete(void* ptr) noexcept {
    std::cout << "delete (unsized)\n";
    free(ptr);
}

void operator delete(void* ptr, size_t) noexcept {
    std::cout << "delete (sized)\n";
    free(ptr);
}

////////////////////////////////////////////////////////////////////////////////

static int next_id = 0;

template <typename T>
class LoggingAllocator {
  public:
    using value_type = T;

    LoggingAllocator() : id(++next_id) { std::cout << "Ctor()" << std::endl; }

    // UB if you uncomment it and comment template vecsion :)

    //   LoggingAllocator(const LoggingAllocator& other): id(++next_id) {
    //     std::cout << "Copy(): " << other.id << " to " << id << std::endl;
    //   }

    template <typename U>
    LoggingAllocator(const LoggingAllocator<U>& other) : id(++next_id) {
        std::cout << "Copy(): " << other.id << " to " << id << std::endl;
    }

    LoggingAllocator& operator=(const LoggingAllocator& other) = delete;

    T* allocate(std::size_t n) {
        std::cout << "Logging (" << id << "): allocate " << n * sizeof(T)
                  << " bytes" << std::endl;
        return static_cast<T*>(operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Logging (" << id << "): deallocate " << n * sizeof(T)
                  << " bytes" << std::endl;
        operator delete(p);
    }

    bool operator==(const LoggingAllocator& other) const { return true; }
    bool operator!=(const LoggingAllocator& other) const { return false; }

    static constexpr std::true_type is_always_equal;

    // Rebind for compatibility
    template <typename U>
    struct rebind {
        using other = LoggingAllocator<U>;
    };

    // Add an ID to track allocator instances
    int id;
};

int main() {
    using String =
        std::basic_string<char, std::char_traits<char>, LoggingAllocator<char>>;

    LoggingAllocator<String> alloc;

    // std::vector<String, LoggingAllocator<String>> v(alloc);
    std::vector<String, std::scoped_allocator_adaptor<LoggingAllocator<String>>>
        v(alloc);

    v.reserve(2);
    std::cout << "---\n";
    v.emplace_back("111");
    v.emplace_back("222");
}

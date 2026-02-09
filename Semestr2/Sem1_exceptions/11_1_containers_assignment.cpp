#include <iostream>
#include <list>
#include <vector>

// operator=() is more likely to support BASIC exception guarantee
// resize() is more likely to support STRONG exception guarantee

static const int MaxExceptionsN = 4;

struct ThrowAfterN {
    inline static int create_count = 0;
    inline static int count = 0;
    int value;

    ThrowAfterN() : value(++create_count) {
        std::cout << "Constructing " << value << "\n";
    }

    ThrowAfterN(const ThrowAfterN& other) : value(++count) {
        std::cout << "Copy " << count << '\n';
        if (count >= MaxExceptionsN) {
            throw std::runtime_error("boom");
        }
    }

    ThrowAfterN& operator=(const ThrowAfterN& other) {
        value = other.value;
        ++count;
        std::cout << "Assigning " << count << ", other.value = " << other.value
                  << '\n';
        if (count >= MaxExceptionsN) {
            throw std::runtime_error("boom");
        }
        return *this;
    }

    ~ThrowAfterN() { std::cout << "Destroying " << value << '\n'; }
};

void ListExaple() {
    std::cout << "Start c1 creation\n";
    std::list<ThrowAfterN> c1(5);
    std::cout << "Start c2 creation\n";
    std::list<ThrowAfterN> c2(2);

    std::cout << "c2.front() before exception: " << c2.front().value << '\n';

    try {
        c2 = c1;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
        // It still will be 2
        std::cout << "Container size after exception: " << c2.size() << "\n";
    }
    // But it will give 1 instead of 6
    std::cout << "c2.front() after exception: " << c2.front().value << '\n';
}

void VectorExample() {
    std::cout << "Start c1 creation\n";
    std::vector<ThrowAfterN> c1(4);
    std::cout << "Start c2 creation\n";
    std::vector<ThrowAfterN> c2(5);

    std::cout << "c2.front() before exception: " << c2.front().value << '\n';

    try {
        c2 = c1;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
        // It still will be 5
        std::cout << "Container size after exception: " << c2.size() << "\n";
    }
    // But it will give 1 instead of 5
    std::cout << "c2.front() after exception: " << c2.front().value << '\n';
}

int main() {
    ListExaple();
    // VectorExample();
}

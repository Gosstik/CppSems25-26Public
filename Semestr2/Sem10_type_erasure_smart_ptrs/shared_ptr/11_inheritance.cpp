#include <iostream>
#include <memory>

// Shared ptr destruct object as T, where T is the type of first created object

struct Base {
    int x;
    Base() { std::cout << "Base()" << std::endl; }
    ~Base() { std::cout << "~Base()" << std::endl; }
};

struct Derived : Base {
    int y;
    Derived() { std::cout << "Derived()" << std::endl; }
    ~Derived() { std::cout << "~Derived()" << std::endl; }
};

int main() {
    std::cout << 1 << std::endl;

    {
        // Virtual destructor is not required !!!
        std::shared_ptr<Derived> dp = std::make_shared<Derived>();
        std::shared_ptr<Base> bp(dp);
        dp.reset();
    }

    std::cout << 2 << std::endl;

    {
        // Virtual destructor is also not required !!!
        std::shared_ptr<Base> bp = std::make_shared<Derived>();
        std::shared_ptr<Derived> dp(std::static_pointer_cast<Derived>(bp));
    }

    std::cout << 3 << std::endl;

    {
        // But here virtual destructor is required
        Base* b = new Derived();
        std::shared_ptr<Base> bp(b);
        std::shared_ptr<Derived> dp(std::static_pointer_cast<Derived>(bp));
        bp.reset();
    }

    std::cout << 4 << std::endl;
}

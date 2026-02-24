#include <iostream>
#include <stdexcept>

// How to clean memory ???
//* Use RAII

// If non-delegating ctor completed successfully but delegating ctor throw then
// dtor WILL BE CALLED before entering catch.

// All constructed bases/members will be destroyed before catch clause in ctor.

// Before any catch clauses in the destructor are entered, all bases and
// non-variant members have already been destroyed. Referencing them is UB.

// Accessing base classes or non-static members in try block in ctor/dtor is UB.

// After catch clause in ctor/dtor exception is rethrown.

struct A {
    A(bool is_thrown) {  // NOLINT
        std::cout << "A\n";
        if (is_thrown) {
            throw std::logic_error("exception in A\n");
        }
    }

    ~A() { std::cout << "~A\n"; }
};

struct S {
    S() try : p(new int(1)), a(true) {
        std::cout << "S\n";
        throw std::logic_error("you shall not pass!!!\n");
    } catch (const std::exception& err) {
        std::cout << "caught in S: " << err.what();

        delete p;  // UB: refer to a non-static member in try block in ctor/dtor
        Clear();  // UB: refer to a non-static member in try block in ctor/dtor

        // throw;  // redundant, rethrow by default for caller handling
        // return ...;  // CE, no return allowed
    }

    ~S() {
        std::cout << "~S";
        Clear();
    }

    void Clear() const {
        std::cout << "Clear\n";
        delete p;
    }

    int* p = nullptr;
    A a;
};

int main() {
    try {
        S s;
    } catch (...) {
        std::cout << "caught!\n";
    }
}

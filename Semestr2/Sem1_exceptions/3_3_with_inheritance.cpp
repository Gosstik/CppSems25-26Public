#include <iostream>

struct Base {
    int a = 0;
};

struct Derived : Base {
    int a = 1;
};

// GtoP = General to Particular
template <typename T>
void GtoP(T to_throw) {
    try {
        throw to_throw;  // NOLINT
    } catch (const Base& obj) {
        std::cout << "Base\n";
        std::cout << "obj.a = " << obj.a << '\n';  // ???
    } catch (const Derived& obj) {                 // NOLINT
        std::cout << "Derived\n";
        std::cout << "obj.a = " << obj.a << '\n';  // ???
    } catch (...) {
        std::cout << "...\n";
    }
}

template <typename T>
void PtoG(T to_throw) {
    try {
        throw to_throw;  // NOLINT
    } catch (const Derived& obj) {
        std::cout << "Derived\n";
        std::cout << "obj.a = " << obj.a << '\n';  // ???
    } catch (const Base& obj) {
        std::cout << "Base\n";
        std::cout << "obj.a = " << obj.a << '\n';  // ???
    } catch (...) {
        std::cout << "...\n";
    }
}

int main() {
    GtoP<Base>({});
    GtoP<Derived>({});

    std::cout << "-------------------\n";

    PtoG<Base>({});
    PtoG<Derived>({});
}

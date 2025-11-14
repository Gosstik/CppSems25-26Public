#include <iostream>

// TODO: same method name

int Do() {
    return 1;
}

struct S {
    static int Do() {
        return 2;
    }

    struct Inner {
        // int Do() {
        //     return 3;
        // }

        int Bar() {
            // ...
            return Do();
        }
    };

    // int Do;
};

int main() {
    S s;
    S::Inner i;
    std::cout << i.Bar() << '\n';
}

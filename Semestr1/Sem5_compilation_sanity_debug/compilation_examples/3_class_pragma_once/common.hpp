#pragma once

struct S;

struct S {
    int Foo() {
        return val;
    }

    int val{};
};

inline int Bar() {
    return 100;
}

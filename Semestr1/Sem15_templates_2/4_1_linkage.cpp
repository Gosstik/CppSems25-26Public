#include <iostream>

// On cppreference:
// https://en.cppreference.com/w/cpp/language/storage_duration.html

// !!! Do not confuse with language linkage:
// https://en.cppreference.com/w/cpp/language/language_linkage.html

// 4 types of linkage
// 1) no linkage (name cannot be used outside of its scope)
// 2) internal (name cannot be used outside of translation unit)
// 3) external (name can be used in another translation unit)
// 4) module

// Linkage type affects on what type of symbol the name will have for linker.

// !!! Function always has linkage

// !!! Linker is single-path. So if name that has been already linked appear,
// it is simple ignored. Linkage of std libraries: libc -> libgcc -> libc

extern int v0;  // external (declaration WITHOUT definition)
// extern int v0 = 1; // declaration WITH definition
static int v1;  // internal

void Foo() {
    extern int y;  // external
}

void Bar() {
    static int z;  // no linkage
}

template <typename T>
void Bar(T);  // external

namespace {

int Buz();  // internal

}  // namespace

struct T;  // external

template <typename T>
struct U;  // external

struct S {
    static int x;  // external
};

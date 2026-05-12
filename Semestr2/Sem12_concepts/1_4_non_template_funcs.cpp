#include <cstddef>

// Non-templated function cannot have a requires clause
// requires clause is not a part of function signature!!!

void Foo()
    requires(sizeof(size_t) == 4)  // CE
{
    // ...
}

int main() {}

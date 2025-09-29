#include <iostream>

void Foo(int) {}

// Function returning function
void (*Bar(int))(int) { return Foo; }

int main() {
    // Read precedence:
    // 1) inside braces
    // 2) right part
    // 3) left part
    // Simple rule: go right when you can, go left when you must
    // More examples with explanation:
    // http://www.unixwiz.net/techtips/reading-cdecl.html

    void (*pf)(int);         // ptr to func
    void (*pfa[10])(int);    // Array of 10 ptrs to func
    void (*(*ppfa)())(int);  // ptr to f that accepts 0 args and returns func
                             // that accepts int and returns void

    size_t** e1[7];                  // ???
    void (*(*pff[10])(int))(int);    // ???
    int (*(*e2)(double, int))(int);  // ???
    int (*(*e3)())(int);             // ???

    int (*e4())(int) = nullptr;      // !!! function declaration
    int a = 0;
    int((b)) = 4;

    char*(*(**foo[][8])())[] = {};  // ???????????????????????????????
}

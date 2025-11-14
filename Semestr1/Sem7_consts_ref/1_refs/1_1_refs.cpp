#include <iostream>

int RefFunc1(int) { return 1; }
int RefFunc2(int) { return 2; }

int main() {
  {
    // Basics
    int x = 5;
    int& y = x;
    ++y;  // increment x
    int z = 7;
    y = z;       // Change value of x, reference cannot rebind
    int& t = y;  // Points to x

    int& r;       // CE (reference requires initializer)
    int& rr = 5;  // CE (5 does not have address)
  }

  {
    // Pointers and references
    int val;
    int* p = &val;
    int& r = *p;  // *p returns int& instead if int

    // Reference to array
    int a[10];
    int(&ra)[10] = a;  // OK

    // Reference to pointer
    int x = 0;
    int* px = &x;
    int*& rpy = px;  // ???

    // Pointer to reference
    int y = 0;
    int& ry = y;
    int&* pry = &ry;  // ???

    // Double reference
    int z = 0;
    int& rz = z;
    int&& rrz = rz;  // ???

    // Array of references
    int& a[3]{x, y, z};
    a[0] = 1;  // ???

    // Reference to function
    int (&rf)(int) = RefFunc1; // ???
    rf = RefFunc2; // ???
  }
}

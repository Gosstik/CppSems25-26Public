#include <iostream>
#include <vector>

int main() {
    {
        // Basics
        int x = 10;
        const int cx = x;
        int const xc = x;  // same as above

        const const const int const const c = 3;

        // c = 3; // CE
        // ++c; // CE
        // const int uc; // CE
    }

    {
        // Pointers and const
        int x = 1;
        int y = 2;
        int* p = &x;

        const int* pc1 = p;  // pointer to const
        int const* pc2 = p;  // same as above
        *pc1 = 1;            // CE
        pc1 = &y;            // OK

        int* const cp = p;  // const pointer
        *cp = 1;            // OK
        cp = &y;            // CE

        int* p2 = pc1;  // CE
        int* p3 = cp;   // OK
    }

    {
        // Dynamic memory allocation
        int* p = new const int(1);                // ???
        const int* cp = new const int(1);         // ???
        const int* up = new const int;            // ???
        /*const*/ int* ap = new const int[10]{};  // ???
    }

    {
        // References and const
        int x = 5;
        const int& cr = x;  // though it is 'reference to const', 'const
                            // reference' is also used
        int const& cr2 = x;  // also possible
        int& const cr3 = x;  // CE

        const int cx = 0;
        int& y = x;   // CE
        int& r = cr;  // CE
    }
}

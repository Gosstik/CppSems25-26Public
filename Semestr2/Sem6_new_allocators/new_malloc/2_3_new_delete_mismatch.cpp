#include <iostream>
#include <list>
#include <vector>

// clang-format off

// It is a bad idea to use different versions (raw and full) for allocation and deallocation.

// ==184331==ERROR: AddressSanitizer: new-delete-type-mismatch on 0x502000000010 in thread T0:
//   object passed to delete has wrong type:
//   size of the allocated type:   8 bytes;
//   size of the deallocated type: 4 bytes.

// clang-format on

int main() {
    int* a = static_cast<int*>(operator new(2 * sizeof(int)));
    // int* a = static_cast<int*>(operator new(sizeof(int)));

    std::cout << *a;

    delete a;
    // operator delete(a);
}

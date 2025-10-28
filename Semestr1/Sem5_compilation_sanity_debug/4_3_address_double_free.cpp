#include <iostream>

int main() {
    int* a = new int(1);
    delete a;
    // delete a;

    a = nullptr;
    delete a;
    delete a;
}

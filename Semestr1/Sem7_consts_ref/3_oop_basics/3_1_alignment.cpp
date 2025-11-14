#include <iostream>

struct Node {
    int data;
    Node* next;
};

static_assert(sizeof(int) == 4);
static_assert(sizeof(Node*) == 8);
static_assert(sizeof(Node) == 16);

////////////////////////////////////////////////////////////////////////////////

struct Node2 {
    char ch1[5];
    char ch2[3];
};

static_assert(sizeof(Node2) == 8);

////////////////////////////////////////////////////////////////////////////////

struct Zip {
    double d;
    char ch2[3];
    int i;
};

static_assert(sizeof(Zip) == 16);

////////////////////////////////////////////////////////////////////////////////

struct Flip1 {
    double d;
    int i1;
    int i2;
};

struct Flip2 {
    int i1;
    double d;
    int i2;
};

static_assert(sizeof(Flip1) == 16);
static_assert(sizeof(Flip2) == 24);

////////////////////////////////////////////////////////////////////////////////

int main() {
    int y = 0;
    std::cin >> y;

    const int x = y;
    // static_assert(x == 0); // CE
}

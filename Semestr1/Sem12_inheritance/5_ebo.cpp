struct Empty {};

struct Base {
    int x;
};

struct Derived1 : Base {
    double y;
};

struct Derived2 : Empty {
    int x;
};

static_assert(sizeof(Empty) == -1);     // ???
static_assert(sizeof(Base) == -1);      // ???
static_assert(sizeof(Derived1) == -1);  // ???
static_assert(sizeof(Derived2) == -1);  // ???

int main() {}

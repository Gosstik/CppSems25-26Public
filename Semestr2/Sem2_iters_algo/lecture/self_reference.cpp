struct S {
    int x;
    explicit S(int x) : x(x) {}
};

struct SelfReference {
    int x;
    int& r;
    explicit SelfReference(int y) : x(y), r(x) {}
};

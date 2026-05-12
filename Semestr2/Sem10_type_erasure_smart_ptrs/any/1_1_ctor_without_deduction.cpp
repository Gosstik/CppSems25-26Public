

struct S {
    template <typename T>
    S(int a) : val(a) {}

    int val;
};

int main() { S s = S<float>(1); };

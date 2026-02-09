template <typename T>
struct Template {};

template <template <class> class T>
struct S {
    T<int> a;
};

int main() { S<Template> s; }

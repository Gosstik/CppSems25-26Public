
// What version to comment?

template <typename T>
void Foo(T&&) {}  // 1

template <typename T>
void Foo(T&) {}  // 2

template <typename T>
void Foo(T) {}  // 3

int main() {
    int x = 1;

    Foo(x);
    Foo(1);
}

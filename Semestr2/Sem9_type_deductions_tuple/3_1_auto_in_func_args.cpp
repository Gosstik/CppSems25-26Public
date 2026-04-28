// auto in function argument list

template <typename T>
void Foo(T x) {}

void Foo(auto x) {}

void Bar(auto... x) {}

int main() {
    // TODO
}

#include <iostream>
#include <memory>

struct A {
  public:
    static std::unique_ptr<A> Create() { return std::make_unique<A>(A{}); }

    // Copy
    // Assign

    void Print() {  // NOLINT
        std::cout << "Print A\n";
    }

  private:
    A() = default;
};

int main() {
    // A a;  // CE
    auto pa = A::Create();
    pa->Print();
}

#include <iostream>
#include <memory>

struct Complex {
    struct Inner {
        Inner() { std::cout << "Inner()" << std::endl; }
        ~Inner() { std::cout << "~Inner()" << std::endl; }
        void DoStuff() {
            std::cout << "Doing stuff with y = " << y << std::endl;
        }
        int y = 1;
    };

    Complex() { std::cout << "Complex()" << std::endl; }
    ~Complex() { std::cout << "~Complex()" << std::endl; }

    int x = 1;
    Inner inner;
};

int main() {
    auto cp = std::make_shared<Complex>();
    std::shared_ptr<int> cx(cp, &cp->x);
    std::shared_ptr<Complex::Inner> cinner(cp, &cp->inner);

    cp.reset();

    std::cout << cx.use_count() << std::endl;  // 2
}

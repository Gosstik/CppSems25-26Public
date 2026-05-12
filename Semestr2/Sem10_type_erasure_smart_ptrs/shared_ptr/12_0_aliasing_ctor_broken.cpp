#include <iostream>
#include <memory>

struct Granny {
    int g = 1;
    Granny() { std::cout << "Granny()" << std::endl; }
    ~Granny() { std::cout << "~Granny()" << std::endl; }
    void SayHi() { std::cout << "Hi from granny!\n"; }
};

struct Mom : Granny {
    int m = 2;
    Mom() { std::cout << "Mom()" << std::endl; }
    ~Mom() { std::cout << "~Mom()" << std::endl; }
    void SayHi() { std::cout << "Hi from mom!\n"; }
};

struct Dad : Granny {
    int d = 3;
    Dad() { std::cout << "Dad()" << std::endl; }
    ~Dad() { std::cout << "~Dad()" << std::endl; }
    void SayHi() { std::cout << "Hi from dad!\n"; }
};

struct Son : Mom, Dad {
    int s = 4;
    Son() { std::cout << "Son()" << std::endl; }
    ~Son() { std::cout << "~Son()" << std::endl; }
    void SayHi() { std::cout << "Hi from son!\n"; }
};

void DoJob(std::shared_ptr<Granny> g) {
    if (auto s = std::dynamic_pointer_cast<Son>(g); s != nullptr) {
        std::cout << s->s << std::endl;
        return;
    }
    if (auto m = std::dynamic_pointer_cast<Mom>(g)) {
        std::cout << m->m << std::endl;
        return;
    }
}

int main() {
    std::shared_ptr<Mom> ms = std::make_shared<Son>();
    std::shared_ptr<Mom> m = std::make_shared<Mom>();

    DoJob(ms);
    DoJob(m);
}

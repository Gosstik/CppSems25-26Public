
struct Granny {
    void Foo() {}

    int g = 0;
};

struct Mom : Granny {
    virtual void Foo() {}

    int m = 0;
};

struct Son : Mom {
    void Foo() override {}

    int s = 0;
};

// ptr -- g -- m -- s
// ^                 --- son and mom
//        ^          --- granny

int main() {
    Son s;
    auto g = dynamic_cast<Granny&>(s);
}

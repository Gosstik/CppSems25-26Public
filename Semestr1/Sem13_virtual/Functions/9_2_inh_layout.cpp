

struct Base {
    virtual void Foo() = 0;

    int x = 0;
};

struct Derived : Base {
    void Foo() override {}

    virtual void Bar() {}

    int y = 1;
};

static_assert(sizeof(Base) == 16);
static_assert(sizeof(Derived) == 16);

// Base::type_info, Base::Foo()
// Derived::type_info --- Derived::Foo() --- Derived::Bar()
// Base::type_info    --- Base::Foo()

// How call works?
// How dynamic_cast works?

int main() {
    Base* b = new Derived();
    b->Foo();
}

// TODO
// public/private/protected

struct Base {
  public:
    int x;

  private:
    int y;

  protected:
    int z;

    // friend struct Derived;
    friend int main();
};

struct Derived : Base {
    void PureVirtualFunc() {
        x = 1;
        y = 1;
        z = 1;
    }

    int x;
};

int main() {
    Derived d;
    d.x = 1;
    d.Base::x = 1;
    d.y = 1;
    d.z = 1;
}

// Without "private" struct must have Standard-Layout
// This prevents issues with pointer casting and C compatibility
struct Base {
  private:  // try to comment
    double d; // try to make it second
    int x;
};

struct Derived : public Base {
    int y;
};

static_assert(sizeof(Base) == 16);
static_assert(sizeof(Derived) == 16);

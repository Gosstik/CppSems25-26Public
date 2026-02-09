
struct Granny {
    int g;

    virtual ~Granny() = default;
};

struct Mom : Granny {
    int m;
};

struct Dad : Granny {
    int d;
};

struct Son : Mom, Dad {
    int s;
};

static_assert(sizeof(Son) == 40);

// ptr -- g -- m -- ptr -- g -- d -- s

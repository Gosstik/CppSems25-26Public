// ODR: One Definition Rule

// No translation unit shall contain more than one definition of any variable,
// function, class type, enumeration type or template [...].

// Every program shall contain exatly exactly one definition of every non-inline
// function or variable that is odr-used in that program outside of discarded
// statement.

// !!! inline does not modify linkage type
// !!! Implicit specializations are inline by default

static inline void Foo() {}  // internal (actually it will be weak symbol)

template <typename T>
void Call(T) {}

//// !!! ODR violation if that specialization is inside .hpp
// template <>
// void Call<int>(int) {}

//// Correct definition inside .hpp
template <>
inline void Call<int>(int) {}

////////////////////////////////////////////////////////////////////////////////

// odr-used == units that require definition
// discarded statement == commands inside constexpr block that is not used

struct S {
    static const int kVal = 5;  // declaration (despite of initializer)
};

int x = S::kVal + 1;  // kVal is not odr-used
const int S::kVal;    // definition

int Addr(const int*) { return 1; }
int y = Addr(&S::kVal);  // kVal is odr-used

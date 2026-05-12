#include <iostream>
#include <type_traits>

template <typename Ret>
struct NoArgsFireOneFunction {
    NoArgsFireOneFunction(Ret (*func)())  // NOLINT(google-explicit-constructor)
        : func_(func) {}

    ////////////////////////////////////////////////////////////////////////////

    // Not working

    // template <std::enable_if_t<!std::is_same_v<Ret, void>>* = nullptr>
    // Ret Call() {
    //     Ret res = func_();
    //     Clear();
    //     return res;
    // }

    // template <std::enable_if_t<std::is_same_v<Ret, void>>* = nullptr>
    // Ret Call() {
    //     func_();
    //     Clear();
    // }

    ////////////////////////////////////////////////////////////////////////////

    // Working

    template <
        typename Ret2 = Ret,
        std::enable_if_t<!std::is_same_v<Ret2, void>>* = nullptr>
    Ret Call() {
        Ret2 res = func_();
        Clear();
        return res;
    }

    template <
        typename Ret2 = Ret,
        std::enable_if_t<std::is_same_v<Ret2, void>>* = nullptr>
    Ret Call() {
        func_();
        Clear();
    }

    void Clear() { func_ = nullptr; }

  private:
    Ret (*func_)() = nullptr;
};

int Foo() {
    std::cout << "Call Foo\n";
    return 42;
}

void Bar() { std::cout << "Call Bar\n"; }

int main() {
    NoArgsFireOneFunction f(Foo);
    NoArgsFireOneFunction b(Bar);

    f.Call();
    b.Call();
}

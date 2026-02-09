
// TAD --- Template Argument Deduction

template <typename Ret, typename Arg>
Ret MyCast(Arg value) {
    return value;
}

int main() {
    int a = 3;

    MyCast(a);              // CE
    MyCast<int>(a);         // OK
    MyCast<int, int>(a);    // OK
    MyCast<int, float>(a);  // Warning
    MyCast<int, int*>(a);   // CE
}

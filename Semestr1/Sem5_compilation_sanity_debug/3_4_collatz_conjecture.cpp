// An infinite loop that produces no observable side effects
// (like printing to console, modifying global variables, or accessing
// volatile memory) causes undefined behavior.

// If Collatz conjecture always ends on 1, program is well formed.
// Otherwise (on some values 1 will not be reached) program contains UB.

// try with -O3 in godbolt
int CollatzConjecture(int i) {
    while (i != 1) {
        if (i % 2 == 0) {
            i /= 2;
        } else {
            i = 3 * i + 1;
        }
    }

    return i;
}

// int CollatzConjectureRecursive(int n) {
//     if (n == 1) {
//         return 1;
//     }
//     if (n % 2 == 0) {
//         return CollatzConjectureRecursive(n / 2);
//     }
//     return CollatzConjectureRecursive(3 * n + 1);
// }

int main() {
    CollatzConjecture(10);
    // CollatzConjectureRecursive(10);
}

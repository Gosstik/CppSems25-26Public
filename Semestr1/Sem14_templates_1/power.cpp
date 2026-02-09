#include <cstddef>

template <typename T>
T Power(T val, size_t deg) {
    if (deg == 0) {
        return 1;
    }
    T acc = T(1);  // id<T>().

    if (val == acc || deg == 1) {
        return val;
    }

    while (deg > 0) {
        if (deg % 2 == 0) {
            val *= val;
            deg /= 2;
        } else {
            acc *= val;
            --deg;
        }
    }

    return acc;
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
T Power2Impl(T val, T acc, size_t deg) {
    if (val == acc || deg == 1) {
        return val;
    }

    while (deg > 0) {
        if (deg % 2 == 0) {
            val *= val;
            deg /= 2;
        } else {
            acc *= val;
            --deg;
        }
    }

    return acc;
}

int Power(int val, size_t deg) {
    if (deg == 0) {
        return 1;
    }
    if (val < 2 || deg == 1) {
        return val;
    }

    return Power2Impl(val, 1, deg);
}

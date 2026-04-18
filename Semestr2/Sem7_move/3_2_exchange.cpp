#include <type_traits>
#include <utility>

// ! noexcept

template <class T, class U = T>
T exchange(T& obj, U&& new_value) {  // NOLINT(readability-identifier-naming)
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}

#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

int main() {
    {
        std::tuple<int, bool, std::string> t = {1, false, "abc"};

        // get by index
        assert(std::get<0>(t) == 1);
        assert(std::get<2>(t) == "abc");

        // get by type
        assert(std::get<int>(t) == 1);
        assert(std::get<bool>(t) == false);
    }

    {
        // non-unique types
        std::tuple<int, bool, int> t = {2, false, 5};

        // get by index
        assert(std::get<0>(t) == 2);
        assert(std::get<2>(t) == 5);

        // get by type
        assert(std::get<int>(t) == 1);       // CE
        assert(std::get<bool>(t) == false);  // OK
    }

    {
        // references

        int i = 10;
        bool b = false;
        long l = 3;
        std::tuple<float, int&, const bool&, long&&> t(
            3.14, i, b, std::move(l));

        static_assert(std::is_same_v<decltype(std::get<0>(t)), float&>);
        static_assert(std::is_same_v<decltype(std::get<1>(t)), int&>);
        static_assert(std::is_same_v<decltype(std::get<2>(t)), const bool&>);
        static_assert(std::is_same_v<decltype(std::get<3>(t)), long&>);  // !!!

        static_assert(
            std::is_same_v<decltype(std::get<0>(std::move(t))), float&&>);
        static_assert(
            std::is_same_v<decltype(std::get<1>(std::move(t))), int&>);  // !!!
        static_assert(
            std::is_same_v<decltype(std::get<2>(std::move(t))), const bool&>);
        static_assert(
            std::
                is_same_v<decltype(std::get<3>(std::move(t))), long&&>);  // !!!
    }
}

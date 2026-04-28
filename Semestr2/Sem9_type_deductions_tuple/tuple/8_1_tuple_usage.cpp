#include <iostream>
#include <tuple>

int main() {
    {
        // Just usage

        std::tuple<int, double, char> t1{1, 2.0, 'a'};
        std::tuple t2{1, 2.0, 'a'};  // CTAD

        // get<I>
        std::cout << "std::get<0>(t1)=" << std::get<0>(t1) << std::endl;
        // assign
        std::get<1>(t1) = 5.0;
        // get<T>
        std::cout << "std::get<char>(t1)=" << std::get<char>(t1) << std::endl;

        auto t3 = std::tuple_cat(t1, t2);
        std::cout << "size(t3)="
                  << std::tuple_size_v<decltype(t3)> << std::endl;
    }

    {
        // std::get examples

        std::tuple<int, double, char> t1{1, 2.0, 'a'};

        // OK
        auto& d1 = std::get<1>(t1);
        // CE, must save value type and const
        auto& d2 = std::get<1>(std::move(t1));

        // t1.double still contains correct value (no move actually)
        auto&& d3 = std::get<1>(std::move(t1));
        // Now t1.double is moved
        auto d4 = std::get<1>(std::move(t1));
    }
}

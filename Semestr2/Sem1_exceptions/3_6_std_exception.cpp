#include <iostream>
#include <stdexcept>

// motivation of deriving from std::exception - ability to catch all exceptions
// as objects and to have at least string description
// (in contrast with ellipsis)

// Diagnostics library: https://en.cppreference.com/w/cpp/error
// <exception> --- contains std::exception and utils
// <stdexcept> --- predefined exceptions in std

// https://en.cppreference.com/w/cpp/error#Exception_categories
// predefined exceptions has ctor from string, but no default ctor

// std::exception (without ctor from string, but has default ctor)
// std::runtime_error
// std::out_of_range
// std::invalid_argument

// hierarchy: https://en.cppreference.com/w/cpp/error/exception

// std::runtime_error --- error on server side
// others --- error on client side

// Custom exception
struct NetworkConnectionFailed : std::runtime_error {
    using std::runtime_error::runtime_error;
};

template <typename T>
void Handler() {
    try {
        throw T();
    } catch (const std::exception& err) {
        std::cout << err.what() << '\n';  // prints "std::exception"
    }
}

template <typename T>
void Handler(const char* str) {
    try {
        throw T(str);
    } catch (const std::exception& err) {
        std::cout << err.what() << '\n';  // prints str
                                          // dynamic_cast also works
    }
}

int main() {
    Handler<std::exception>();
    // Handler<std::exception>("my exception"); // CE

    // Handler<std::runtime_error>(); // CE
    Handler<std::runtime_error>("runtime error!");
    Handler<std::out_of_range>("out of range!");
    Handler<std::invalid_argument>("invalid argument!");
    Handler<NetworkConnectionFailed>("no available sockets");
}

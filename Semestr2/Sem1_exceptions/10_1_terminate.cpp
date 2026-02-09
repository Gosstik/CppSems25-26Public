#include <exception>
#include <iostream>

// get_terminate: https://en.cppreference.com/w/cpp/error/get_terminate
// set_terminate: https://en.cppreference.com/w/cpp/error/set_terminate
// abort (from C): https://en.cppreference.com/w/cpp/utility/program/abort

// std::terminate() vs abort() vs exit()
// https://stackoverflow.com/questions/2820285/abort-terminate-or-exit

// std::terminate in contrast with abort() will print type of thrown object
// and content of e.what() if it is inherited fro std::exception

// Whether stack unwinding is done when an exception goes completely uncaught
// is implementation defined.
// In most implementations destructors of variables with automatic, thread
// local (since C++11) and static storage durations are not called.

// buffer of std::cout is not obligatory flushes in default terminate_handler
// One must flush it himself. If program is killed by OS, std::terminate would
// not be called. In order to be convinced that buffer is cleared, one can
// disable buffering:
// https://stackoverflow.com/questions/1377084/unbuffered-output-with-cout

void FirstHandler() {
    std::cout << "First custom terminate function\n" << std::flush;
    std::abort();
}

void SecondHandler() {
    std::cout << "Second custom terminate function\n" << std::flush;
    std::abort();
}

int main() {
    // set
    int n{};
    std::cin >> n;
    std::set_terminate(n == 0 ? FirstHandler : SecondHandler);

    // get
    std::terminate_handler th = std::get_terminate();
    if (th == FirstHandler) {
        std::cout << "FirstHandler is set\n" << std::flush;
    } else if (th == SecondHandler) {
        std::cout << "SecondHandler is set\n" << std::flush;
    } else {
        std::cout << "Unknown handler is set\n" << std::flush;
    }

    // test
    throw 1;
}

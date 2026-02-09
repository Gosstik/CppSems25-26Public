#include <exception>
#include <iostream>

void TerminateHandler() {
    std::cout << "First custom terminate function" << std::endl;

    std::exception_ptr eptr = std::current_exception();
    if (eptr) {
        std::cout << "Terminate is called because of exception" << std::endl;
        // catch is the only way to get info from exception_ptr
        try {
            // ??? throw exception inside terminate
            std::rethrow_exception(eptr);
        } catch (std::exception& e) {
            std::cout << typeid(e).name() << '\n';
            std::cout << "info: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unhandled exception" << std::endl;
        }
    }
    std::cout << "Call to abort()" << std::endl;
    std::abort();
}

int main() {
    std::set_terminate(TerminateHandler);

    std::terminate();
    // throw 1;
}

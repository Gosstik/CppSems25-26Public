// Writing template code we should consider that methods of type T may
// throw exceptions.

//// 4 levels of exception guarantee:
// 1) Nothrow
// 2) Strong (vector)
// 3) Basic (consistent, but unpredictable)
// 4) No guarantee

// exception-neural guarantee (std:sort, std::copy) --- just pass exception for
// handling on higher levels.

// https://en.cppreference.com/w/cpp/language/exceptions

// !!! trick with back() and pop_back() in vector
// why pop_back() does not return T ???

// !!! Standard library assumes that dtors are noexcept

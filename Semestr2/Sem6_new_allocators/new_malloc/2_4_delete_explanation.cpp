// clang-format off

// int* ptr = new int(1);
// ... some staff ...
// delete ptr;
//      |
//     \|/
// ptr->~T();  // Call destructor (no-op for int)
// operator delete(ptr, sizeof(T));  // Deallocate sizeof(T) bytes - sized allocation (since c++14)

// clang-format on

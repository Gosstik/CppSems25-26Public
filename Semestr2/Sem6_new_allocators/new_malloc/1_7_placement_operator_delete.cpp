// Non-allocating placement deallocation functions
// void operator delete  ( void* ptr, void* place ) noexcept; (13)
// void operator delete[]( void* ptr, void* place ) noexcept; (14)

////////////////////////////////////////////////////////////////////////////////

//// Your code

// alignas(MyClass) char buffer[sizeof(MyClass)];

// MyClass* obj = new (buffer) MyClass(-1);  // constructor throws!
// //                  ^^^^^^
// //                  this is "place"

////////////////////////////////////////////////////////////////////////////////

//// Actual code

// //                                  ┌─── your buffer
// //                                  ▼
// void* mem = operator new(sizeof(MyClass), buffer);
// //    ^^^                                 ^^^^^^
// //    │                                   "ptr" parameter of operator new
// //    │                                   (returned as-is)
// //    └── the returned pointer

// try {
//     new (mem) MyClass(-1);  // THROWS!
// } catch (...) {
//     operator delete(mem, buffer);
//     //              ^^^  ^^^^^^
//     //              ptr  place (your original buffer)
//     throw;
// }

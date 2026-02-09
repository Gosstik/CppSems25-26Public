//// 4 standard operators that throws exceptions:
// 1) throw
// 2) new (std::bad_alloc)
// 3) dynamic_cast (why other casts do not throw? --- compile time checked)
// 4) typeid

//// Container methods:
// vector.at(), map.at()
// vector.reserve() // std::length_error
// more on cppreference

// try/catch - time consuming operation, much more than new/delete.

// google codestyle forbids exception usage

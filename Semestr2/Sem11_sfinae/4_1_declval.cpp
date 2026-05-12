
// See implementation of has_method_construct for details.

//// Why do we need that function ???
// We want to get object of type T in meta functions to call methods on him,
// but using T() is not always correct because ctor with 0 arguments may not
// exist

// TODO: see on stackoverflow
//// Why T&& instead of T ???
// Handle case when T is incomplete type. And to avoid specialization creation
// for template types.

//// Why T&& instead of T& ???
// To save value category.

//// Why on cppreference std::add_rvalue_reference instead of T&& ???
// To handle T = void

template <typename T>
T&& declval() noexcept;  // NOLINT(readability-identifier-naming)

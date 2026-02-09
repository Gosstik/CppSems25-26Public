// clang-format off

// Is required only in cases where Derived class is deleted through pointer to the base class.
// https://stackoverflow.com/questions/56305006/is-it-necessary-to-have-virtual-destructor-if-the-derived-class-only-contains-au
//
// In standard (since c++11, [expr.delete]):
// In a single-object delete expression, if the static type of the object to be deleted is not similar (7.3.6) to its
// dynamic type and the selected deallocation function (see below) is not a destroying operator delete, the static
// type shall be a base class of the dynamic type of the object to be deleted and the static type shall have a
// virtual destructor or the behavior is undefined. In an array delete expression, if the dynamic type of the
// object to be deleted is not similar to its static type, the behavior is undefined.

// clang-format on

// default ctor
// size()
// empty()
// data()
// swap()
// back/front() ???
// operator[] ???

// Why operator[] is not noexcept in vector?
// Only those functions that are ALWAYS succeeded should be marked noexcept.
// operator[] may cause UB

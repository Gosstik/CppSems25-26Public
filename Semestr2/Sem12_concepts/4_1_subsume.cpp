
// https://en.cppreference.com/w/cpp/language/constraints#Partial_ordering_of_constraints

// P = (A) or (B) or (C)
// Q = (D) and (E)

// P subsumes Q (P => Q; P is a special case of Q) if:
// A => D, E
// B => D, E
// C => D, E

// A => D, E means that for any atomic constraint in D and E exists atomic
// constraint in A that is SYNTACTICALLY identical to D's or E's one

// !!! overload by P and Q where !((P => Q) || (Q => P)) is IFNDR

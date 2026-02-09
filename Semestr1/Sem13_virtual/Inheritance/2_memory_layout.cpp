// ptr stores:
// 1) offsets of virtual bases (to access their data members)
// 2) top offset (offset from structure start, for casts)

// Examples:

// 1) All virtual (Granny offset = 32)
// ptr | m | padding_4 | ptr | d | s | g | padding_4

// 2) Only one Granny is virtual
// 2.1) Mom: virtual Granny
// ptr | m | g | d | s | g

// !!! Just Mom (Granny offset = 12):
// ptr | m | g

// 2.2) Dad: virtual Granny
// g | m | ptr | d | s | g

// !!! Just Dad (offset = 12):
// ptr | d | g

// 3) Son virtually inherits both Mom and Dad
// ptr | s | g | m | g | d

// 4) Son has virtual Mom and Dad, Mom has virtual Granny
// ptr | s | ptr | m | g | d | g

// Example of allocator that share the same source (global pool).
// !!! Copy of allocator must not copy internal array (requires shared_ptr).
// If pool is located on stack - such allocator is called "stack allocator"

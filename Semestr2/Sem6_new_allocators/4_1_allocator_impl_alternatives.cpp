// clang-format off

// Actually only two alternatives are possible:
// 1) If allocators always share the same source (global pool), they can propagate because it doesn't matter - allocators are stateless.
// 2) If allocators can have different memory sources (like different arenas), they should not propagate on container copy - allocators are stateful.

// Actually, 2) is not fully correct. It is much simpler to make all allocators not propagate on container copy.
// But actually, when pocca=true, stl container must check allocators equality and if allocators are not equal,
// container will clear existing memory by old allocator and allocate new memory by new allocator.

// !!! operator=() in stl containers (at least vector and list) provide basic exception guarantee.
// About exception safety of containers in stndard:
// [container.reqmts] 66 ... all container types defined in this Clause meet the following additional requirements
// There no information about exception safety of operator=(), only for modify functions.

// Destuctors must not throw exceptions:
// [res.on.exception.handling]

// allocators that do not propagate at all are named arena-based allocators (e.g. ptmalloc)

// TODO: FreeList allocator

// clang-format on

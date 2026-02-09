#include <unordered_map>

template <typename T>
struct ContainerWrapper;

// Valid spec
template <typename Key, typename Value>
struct ContainerWrapper<std::unordered_map<Key, Value>> {};

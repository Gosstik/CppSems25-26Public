
// push_back(const T& val) ---> new (ptr) T(value);
// push_back(T&& val) ---> new (ptr) T(std::move(value));

// emplace_back(Args&&... args) ---> new (ptr) T(std::forward<Args>(args)...);

#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>

// https://en.cppreference.com/w/cpp/utility/hash

struct Person {
    std::string name;
    size_t age;
    bool operator==(const Person&) const = default;  // since C++20
};

// Custom hash can be a standalone function object.
struct MyHash {
    std::size_t operator()(const Person& s) const noexcept {
        std::size_t name_hash = std::hash<std::string>{}(s.name);
        return name_hash ^ (s.age << 1);  // or use boost::hash_combine
    }
};

// Custom specialization of std::hash can be injected in namespace std.
template <>
struct std::hash<Person> {
    std::size_t operator()(const Person& s) const noexcept {
        std::size_t name_hash = std::hash<std::string>{}(s.name);
        return name_hash ^ (s.age << 1);  // or use boost::hash_combine
    }
};

void TestHash() {
    Person p1{"Mark", 10};
    Person p2{"Tod", 42};

    std::unordered_map<Person, int, MyHash> rating = {{p1, 100}, {p2, 420}};
    std::cout << "MyHash:\n";
    for (auto const& item : rating) {
        const Person& p = item.first;
        std::cout << p.name << ' ' << p.age << ' ' << item.second << '\n';
    }

    std::cout << "\nstd::hash:\n";
    std::unordered_map<Person, int> rating_std = {{p1, 100}, {p2, 420}};
    for (auto const& item : rating_std) {
        const Person& p = item.first;
        std::cout << p.name << ' ' << p.age << ' ' << item.second << '\n';
    }
}

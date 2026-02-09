#include <algorithm>
#include <string>
#include <vector>

// Pointers to methods: callbacks in qt

struct Employee {
    std::string first_name;
    std::string surname;
    std::string address;
};

class SortFunctor {
  public:
    explicit SortFunctor(std::string Employee::* field) : field_(field) {}

    bool operator()(const Employee& lhs, const Employee& rhs) const {
        return lhs.*field_ < rhs.*field_;
    }

  private:
    std::string Employee::* field_;
};

void SomeFunction(std::vector<Employee>& emploees, const SortFunctor& sort_fn) {
    std::sort(emploees.begin(), emploees.end(), sort_fn);
}

int main() {
    // int Employee::* field = nullptr; // OK

    std::vector<Employee> emploees;

    // ...
    // Fill it somehow
    // ...

    SortFunctor first_name_comparator(&Employee::first_name);
    SomeFunction(emploees, first_name_comparator);

    // ...

    SortFunctor address_comparator(&Employee::address);
    SomeFunction(emploees, address_comparator);
}

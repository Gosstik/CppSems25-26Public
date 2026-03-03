#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// std::hash<std::string_view>
// https://en.cppreference.com/w/cpp/string/basic_string_view/hash

struct Student {
    std::string name;
    int age;
};

int main() {
    std::vector<std::string> names{"Nick", "James", "Carl"};
    std::vector<int> marks{3, 5, 4};

    // !!! NEVER DO THIS
    std::unordered_map<std::string_view, int> name_to_marks;
    for (size_t i = 0; i < names.size(); ++i) {
        name_to_marks.insert({names[i], marks[i]});
    }
    for (auto& p : name_to_marks) {
        std::cout << p.first << " received " << p.second << std::endl;
    }
    names.pop_back();  // names_to_marks contains invalid view
                       // ...

    //////////////////////////////////////////////////////////////////////////////

    // std::unordered_map<std::string_view, int> name_to_course;
    // name_to_course.insert({"Nick", 1});
    // name_to_course.insert({"James", 4});
    // name_to_course.insert({"Carl", 3});
    // name_to_course.insert({std::string("Caroline"), 10});

    // // Is it valid?
    // for (auto p: name_to_course) {
    //   std::cout << p.first << std::endl;
    // }
}

#include <iostream>
#include <memory>

struct My;

struct My {
    std::shared_ptr<My> val;
    My() { std::cout << "CONSTRUCT" << std::endl; }
    ~My() { std::cout << "DESTURCT" << std::endl; }
};

// a, b
// a->b
// b->a

signed main() {
    My* my_1 = new My();
    My* my_2 = new My();
    std::shared_ptr<My> sp1(my_1);
    std::shared_ptr<My> sp2(my_2);
    sp1->val = sp2;
    sp2->val = sp1;
    std::cout << sp1.use_count() << std::endl;  // 2
    std::cout << sp2.use_count() << std::endl;  // 2
    return 0;
}

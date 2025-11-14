// implicit cast from int** to const int** is forbidden
// implicit cast from int** to const int* const* is allowed

// Source:
// https://isocpp.org/wiki/faq/const-correctness#constptrptr-conversion

class Class {
  public:
    void Modify();  // make some modification to the this object
};

int main() {
    const Class x;  // NOLINT
    Class* p;
    const Class** q = &p;  // q now points to p; this is (fortunately!) an error
    *q = &x;               // p now points to x
    p->Modify();           // Ouch: modifies a const Foo!!
                           // ...
}

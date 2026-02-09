#include <iostream>

// Polymorphism: create vector of shapes and iterate over them.

struct Shape {  // NOLINT
    virtual double Area() const = 0;
    virtual ~Shape() = default;
};

double Shape::Area() const { return 2; }

struct Rectangle : Shape {
    double Area() const override { return 4; }
};

int main() {
    // Shape sh; // CE

    Rectangle rect;
    Shape& shape = rect;

    std::cout << shape.Area() << '\n';         // 4
    std::cout << shape.Shape::Area() << '\n';  // 2
}

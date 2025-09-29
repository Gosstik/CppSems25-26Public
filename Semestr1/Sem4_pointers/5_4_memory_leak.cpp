#include <iostream>

// Use htop

void Foo() {
	int* p = new int(5);
	std::cout << p << ' ' << *p << '\n';
	// delete p;
}

void Bar() {
	int* p = new int[1000];
	std::cout << p << ' ' << *p << '\n';
	// delete[] p;
}

int main() {
	while (true) {
		Foo();
    // Bar();
	}
}

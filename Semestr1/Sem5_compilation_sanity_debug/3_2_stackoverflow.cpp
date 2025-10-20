#include <iostream>

// Try with -O2 to see tail recursion optimization
// Use godbolt (difference between call and jmp)

void Foo(int a) {
	std::cout << a << '\n';
	Foo(a + 1); // RE, likely segmentation Fault
}

int main() {
	Foo(1);
}

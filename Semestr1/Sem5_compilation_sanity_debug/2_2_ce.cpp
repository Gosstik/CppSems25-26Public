#include <iostream>
#include <vector>


int main() {
	//// CE
	\\; // CE, lexical

	{
		int x = 0;
		std::cout << x +; // CE, syntactic
	}

	{
		"abc" + 5.0f; // CE, semantic
	}
}

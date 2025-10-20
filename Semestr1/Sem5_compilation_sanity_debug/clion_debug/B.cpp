#include <cstdio>
#include <iostream>

int main() {
  size_t size = 0;
  size_t capacity = 4;
  char** stack = new char* [capacity] {};
  char cmd[5] = {};  // "clean" is the longest

  size_t ops_count = 5;
  for (size_t i = 0; i < ops_count; ++i) {
    scanf("%[^ \n]", cmd);
    printf("cmd = %s\n", cmd);
    if (cmd[0] == 'p' && cmd[1] == 'u') {  // push
      if (size == capacity) {
        // reallocate
      }
      // %ms allocates memory for you, you must clear it with free()
      scanf("%ms", &stack[size]);
      ++size;
    } else if (cmd[0] == 'b') {         // back
      printf("%s\n", stack[size - 1]);  // size might be = 0
    }
    // other logic
    if (i + 1 != ops_count) {
      scanf("\n");  // reading trailing \n
    }
  }

  // cleaning
  for (size_t i = 0; i < capacity; ++i) {
    free(stack[i]);
  }
  delete[] stack;
}

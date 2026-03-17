#include <stdio.h>
#include <stdlib.h>

// https://www.stroustrup.com/bs_faq2.html#void-ptr

int main() {
    char i = 0;
    char j = 0;
    char* p = &i;
    void* q = p;
    int* pp = q; /* unsafe, legal C, not C++ */

    printf("%d %d\n", i, j);
    *pp = -1; /* overwrite memory starting at &i */
    printf("%d %d\n", i, j);

    int* p1 = malloc(4 * sizeof(int));
    free(p1);
}

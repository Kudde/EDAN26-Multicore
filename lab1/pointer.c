#include <stdio.h>

int int main() {
        int term;
        int *p = &term;
        printf("p: %d\n", p);
        printf("p*: %d\n", *p);
        printf("term: %d\n", term);
        return 0;
}

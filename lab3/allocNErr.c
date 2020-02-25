#include <stdio.h>
#include <stlib.h>

void error(const char* msg) {

}

int main(void) {
        size_t  size;
        int*    a;
        if (scanf("%zu",&size) != 1)    // scanf() return nbr of sucessfully imported datatypes
                error("invalid size");
        a = malloc(size*sizeof(int));   // Points to a to save memory and check if success
        if (a == NULL)
                error("out of memory");


        free(a);                        // Free memory, Garbage collection kinda

        return 0;
}

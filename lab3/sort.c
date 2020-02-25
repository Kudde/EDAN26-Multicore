#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#define NBR_TREADS      (8)

typedef struct quick_a {
        double  *A;
        int     low;
        int     high;
        int     threads;

} quick_a;


static double sec(void) {
        struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec/1000000.0);
}


static int cmp(const void* ap, const void* bp) {
        double xx = *(double*)ap;
        double yy = *(double*)bp;
        if (xx < yy) return -1;
        if (xx > yy) return  1;
        return 0;
}


int partition(double *A, int low, int high) {
        double pivot = A[low];
        int i = low - 1;
        int j = high + 1;
        while (1) {

                do
                        ++i;
                while (A[i] < pivot);

                do
                        --j;
                while (A[j] > pivot);


                if (i < j) {
                        double temp = A[i];
                        A[i] = A[j];
                        A[j] = temp;

                } else
                        return j;

        }
}


void *pqsort(void *ap) {
        quick_a *a = ap;
        double *A = a->A;
        int low = a->low;
        int high = a->high;
        int threads = a->threads;


        if (low < high) {
                int p = partition(A, low, high);

                // Low
                quick_a a_low = {A, low, p, threads/2};
                pthread_t t;
                if (threads > 1) {
                        pthread_create(&t, NULL, pqsort, &a_low);

                }

                else {
                        if(threads == 1){
                                printf("load %d \n", high-low);

                        }
                        pqsort(&a_low);
                }



                // High
                quick_a a_high = {A, p + 1, high, threads/2};
                pqsort(&a_high);



                if (threads > 1) {
                        pthread_join(t, NULL);



                }
        }
        return NULL;
}


int main(int ac, char** av) {

        int n = 20000000;
        int i;
        double*         a;
        double*         b;
        double start, end;

        if (ac > 1)
                sscanf(av[1], "%d", &n);

        srand(getpid());

        a = malloc(n * sizeof a[0]);
        b = malloc(n * sizeof b[0]);
        for (i = 0; i < n; i++) {
                a[i] = rand();
                b[i] = a[i];
        }

        // Par
        start = sec();
        quick_a sa = {a, 0, n-1, NBR_TREADS};
        pqsort(&sa);
        end = sec();
        printf("par %1.2f s\n", end - start);

        // Seq
        start = sec();
        qsort(b, n, sizeof b[0], cmp);
        end = sec();
        printf("seq %1.2f s\n", end - start);


        // Compare
        for (i = 0; i < n; i++)
                assert(a[i] == b [i]);




        free(a);
        free(b);
        return 0;
}

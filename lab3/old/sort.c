#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>

#define N_T	(4)

pthread_mutex_t	t_sem;

static double sec(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec/1000000.0);
}

void par_sort(
	void*		base,	// Array to sort.
	size_t		n,	// Number of elements in base.
	size_t		s,	// Size of each element.
	int		(*cmp)(const void*, const void*)) // Behaves like strcmp
{
}

static int cmp(const void* ap, const void* bp)
{
	double xx = *(double*)ap, yy = *(double*)bp;
         if (xx < yy) return -1;
         if (xx > yy) return  1;
         return 0;

}
void *PrintHello(void *threadid)
 {
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, A thread #%ld!\n", tid);
    pthread_exit(NULL);
 }

int main(int ac, char** av)
{
	int		n = 200;
	int		i;
	double*		a;
	double*		b;
	double		start, end;

	if (ac > 1)
		sscanf(av[1], "%d", &n);

	srand(getpid());

	a = malloc(n * sizeof a[0]);
	for (i = 0; i < n; i++){
		a[i] = rand();
		b[i] = a[i];
		printf("%f\n", a[i]);

	}
	printf("%s\n", "---------");





#ifdef PARALLEL
	start = sec();
	par_sort(a, n, sizeof a[0], cmp);
#else
	qsort(a, n, sizeof a[0], cmp);
#endif

	for (i = 0; i < n; i++){
		printf("%f\n", a[i]);

	}

	pthread_t threads[N_T];



	for (long i = 0; i < N_T; i++) {
		printf("In main: creating thread %ld\n", i);
		pthread_create(&threads[i], NULL, PrintHello, (void *)i);
	}

	for (i = 0; i < N_T; i++) {
		pthread_join(threads[i], NULL);
	}

	end = sec();

	printf("%1.2f s\n", end - start);

	free(a);

	return 0;
}

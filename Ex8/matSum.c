#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n, i;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) return 1;

    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));
    int *c = (int*)malloc(n * sizeof(int));

    printf("\n=== Array A ===\n");
    for (i = 0; i < n; i++) {
        a[i] = rand() % 10;
        printf("%d\t", a[i]);
    }

    printf("\n\n=== Array B ===\n");
    for (i = 0; i < n; i++) {
        b[i] = rand() % 10;
        printf("%d\t", b[i]);
    }

    printf("\n\n=== Parallel Computation ===");
    printf("\nMax threads available: %d\n", omp_get_max_threads());

    // Start timing
    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
       }
    for(i=0;i<10;i++){
            printf("Thread %d: c[%d] = %d + %d = %d\n",
               omp_get_thread_num(), i, a[i], b[i], c[i]);
    }


    // End timing
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    printf("\n=== Resulting Array C (Sum) ===\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", c[i]);
    }

    printf("\n\n=== Execution Time ===\n");
    printf("Parallel section took: %.6f seconds\n", execution_time);

    free(a);
    free(b);
    free(c);
    return 0;
}

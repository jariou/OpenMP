#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

/*Integration serial version*/
double Integration_gold(int nSteps)
{
    double start = omp_get_wtime();
    double result = 0, x = 0;
    int i;
    double delta = 1 / (double) nSteps;
    for( i = 0; i < nSteps; i++){
        x = (i + 0.5) * delta;
        result += 4.0 / (1 + x * x);
    }
    printf("Integration_gold time:%f\n", omp_get_wtime() - start);
    return result * delta;
}

double Integration_MP(int nSteps)
{
    double start = omp_get_wtime();
    double result = 0;
    int i;
    double delta = 1 / (double) nSteps;
    #pragma omp parallel
    { 
            double x;
        #pragma omp parallel for reduction (+:result)
        for( i = 0; i < nSteps; i++){
            x = (i + 0.5) * delta;
            result += 4.0 / (1 + x * x);
        }
    }

    printf("Integration_gold time:%f\n", omp_get_wtime() - start);
    return result * delta;
}

int main()
{
    int nSteps = 100000000;
    printf("Gold result: %f\n", Integration_gold(nSteps));
    printf("OpenMP result: %f\n", Integration_MP(nSteps));
    return 0;
}

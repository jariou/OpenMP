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
    double delta = 1 / (double) nSteps;
    int j;
    //avoid conflicts
    double resultSet[NUM_THREADS];
    omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
    {
        double x;
        int threadIdx = omp_get_thread_num();
        int nThreads = omp_get_num_threads();
        int i;
        resultSet[threadIdx] = 0;
        for( i = threadIdx, resultSet[threadIdx] = 0 ; i < nSteps; i += nThreads ){
            x = (i + 0.5) * delta;
            resultSet[threadIdx] += 4.0 / (1 + x * x);
        }
    }
    for(j = 0; j < NUM_THREADS; j++)
        result += resultSet[j];
    
    printf("Integration_MP time:%f\n", omp_get_wtime() - start);
    return result * delta;
}

int main()
{
    int nSteps = 10000000;
    printf("Gold result: %f\n", Integration_gold(nSteps));
    printf("OpenMP result: %f\n", Integration_MP(nSteps));
    return 0;
}

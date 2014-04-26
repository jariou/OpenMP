#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 8

/*Integration serial version*/
double Integration_gold(int nSteps)
{
    double result = 0, x = 0;
    int i;
    double delta = 1 / (double) nSteps;
    for( i = 0; i < nSteps; i++){
        x = (i + 0.5) * delta;
        result += 4.0 / (1 + x * x);
    }

    return result * delta;
}

double Integration_MP(int nSteps)
{
    double result = 0, x = 0;
    double delta = 1 / (double) nSteps;
    int i;
    //avoid conflicts
    double resultSet[NUM_THREADS];
    omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
    {
        int threadIdx = omp_get_thread_num();
        int nThreads = omp_get_num_threads();
        printf("threadIdx (%d). nThreads(%d)\n", threadIdx, nThreads);
        resultSet[threadIdx] = 0;
        int shift = threadIdx * nSteps / nThreads;
        for( i = shift; i < shift + nSteps/nThreads; i++){
            x = (i + 0.5) * delta;
            resultSet[threadIdx] += 4.0 / (1 + x * x);
        }
        printf("threadIdx (%d). resultSet(%f)\n", threadIdx, resultSet[threadIdx]* delta);
    }

    for(i = 0; i < NUM_THREADS; i++)
        result += resultSet[i];
    
    return result * delta;
}

int main()
{
    int nSteps = 10000;
    printf("Gold result: %f\n", Integration_gold(nSteps));
    printf("OpenMP result: %f\n", Integration_MP(nSteps));
    return 0;
}

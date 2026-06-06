//Version--2 of PI problem
//We try to solve the race condition problem by using array and each thread calculate it's partial sum and store it in slot of the array 
//we still have the problem of false sharing
#include <iostream>
#include <omp.h>
#include <iomanip>
using namespace std;

static long num_steps = 100000;
double step;

#define NUM_THREADS 4

int main()
{
    int i, nthreads;
    double pi;

    double sum[NUM_THREADS];

    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int id, nthrds;
        int j;          //we use this local loop counter — avoids race on shared 'i'
        double x;

        id     = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id == 0) nthreads = nthrds;


        sum[id] = 0.0;
        for (j = id; j < num_steps; j += nthrds) {
            x = (j + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }


    for (i = 0, pi = 0.0; i < nthreads; i++)
        pi += sum[i] * step;

    cout<<"PI =  "<<fixed << setprecision(15) << pi <<endl;
    return 0;
}

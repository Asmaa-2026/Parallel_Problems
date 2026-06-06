#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std;

static long num_steps = 100000;
double step;

#define NUM_THREADS 4
#define PAD 8   // 64-byte cache line

int main()
{
    int i, nthreads;
    double pi;
    double sum[NUM_THREADS][PAD];

    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int id, nthrds, j;
        double x;

        id     = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id == 0) nthreads = nthrds;

        sum[id][0] = 0.0;
        for (j = id; j < num_steps; j += nthrds) {
            x = (j + 0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }

    for (i = 0, pi = 0.0; i < nthreads; i++)
        pi += sum[i][0] * step;

    cout<<"PI =  "<<fixed << setprecision(15) << pi <<endl;
    return 0;
}

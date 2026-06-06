#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std;

static long num_steps = 100000000;
double step;

#define NUM_THREADS 4

int main()
{
    int nthreads = 0;
    double pi = 0.0;

    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int id, nthrds, j;
        double x, sum = 0.0;

        id     = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id == 0) nthreads = nthrds;

        for (j = id; j < num_steps; j += nthrds) {
            x = (j + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }


        #pragma omp critical
        pi += sum * step;
    }

    cout<<"PI =  "<<fixed << setprecision(15) << pi <<endl;
    return 0;
}

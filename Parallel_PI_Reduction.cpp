#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std;

static long num_steps = 100000000;
double step;

int main()
{
    int i;
    double x, pi, sum = 0.0;

    step = 1.0 / (double)num_steps;

    #pragma omp parallel
    {
        double x_local;

        #pragma omp for reduction(+:sum)
        for (i = 0; i < num_steps; i++) {
            x_local = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x_local * x_local);
        }
    }

    pi = step * sum;
    cout<<"PI =  "<<fixed << setprecision(15) << pi <<endl;
    return 0;
}
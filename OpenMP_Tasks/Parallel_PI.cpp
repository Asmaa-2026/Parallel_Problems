//Version--1 of PI problem:- 
//This code convert sequential PI problem into Parallel solution but it has race condition because all threades access the shared variables
#include<iostream>
#include <iomanip>
#include<omp.h>

using namespace std;

static long num_steps=10000;
double step;

#define NUM_THREADS 4

int main()
{
  double pi=0.0;
  double sum=0.0;
  int nthreads;

  step=1.0/(double)num_steps;

  #pragma omp parallel num_threads(NUM_THREADS)
  {
    int i,id;
    double x;
    id=omp_get_thread_num();
    nthreads=omp_get_num_threads();

    //cyclic distribution
    for(i=id;i<num_steps;i+=nthreads)
    {
      x=(i+0.5)*step;
      sum+=4.0/(1.0+(x*x));
    }

    pi+=sum*step;

  }
  cout<<"PI =  "<<fixed << setprecision(15) << pi <<endl;
  return 0;
}

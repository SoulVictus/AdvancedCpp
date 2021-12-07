#include <stdio.h> 
#include <time.h> 
#include <omp.h> 


int main() 
{
    omp_set_num_threads(2);
    const int N = 1000000000; 
    int i = 0; 
    double sum = 0; 
    clock_t t0 = clock(); 

    #pragma omp parallel for private(i) reduction(+:sum) 
        for (i = N-1; i >= 0; --i) 
        { 
            sum += 1.0/(i+1.0);
        } 

    clock_t t1 = clock(); 
    printf("s = %g\n", sum); 
    printf("t = %g\n", ((double)t1 - t0)/CLOCKS_PER_SEC); 
}
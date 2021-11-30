#include <iostream>
#include <omp.h>

int main()
{
    #pragma omp parallel
    std::cout << "Witaj z wątku nr " << omp_get_thread_num() << " spośród " << omp_get_num_threads() << "\n";

    return 0;
}
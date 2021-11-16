#include <iostream>

template<long long int a, long long int dimensions>
constexpr long long int hypercube()
{
    if (a < 0 || dimensions < 0)
        return -1;
    
    std::size_t result = 1;

    for (std::size_t i = 0; i < dimensions; i++)
    {
        result *= a;
    }

    return result;
}


int main()
{
    std::cout << hypercube<5, 20>() << '\n';
}
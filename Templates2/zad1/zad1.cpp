#include <iostream>
#include <string>
#include <cstring>


template <class T, class U>
auto add1(T & a, U & b) -> decltype(a + b)
{
    return a + b;
}

template<class T, class U>
auto add1(T* a, U* b) -> decltype(*(a)+*(b))
{
    return *(a) + * (b);
}

std::string add1(const char* a,const char* b)
{
    return std::string(a) + std::string(b);
}

int main()
{
    int a = 30;
    float b = 20.4;

    int* ptr1 = &a;
    float* ptr2 = &b;

    const char* text1 = "ala ma ";
    const char* text2 = "kota";

    std::cout << add1(ptr1, ptr2) << "\n";
    std::cout << add1(text1, text2) << "\n";
    std::cout << add1(a, b) << "\n";
    
    return 0;
}
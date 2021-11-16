#include <iostream>
#include <string>

template <class T, class U>
auto add1(T const& a, U const& b) -> decltype(a + b)
{
    return a + b;
}

template <class T, class U, class F>
auto add2(T const& a, U const& b, F op) -> decltype(op(a, b))
{
    return op(a, b);
}

int addInt(int a, int b)
{
    return a + b;
}

std::string addString(std::string a, std::string b)
{
    return a + b;
}

int main()
{
    int a = 30;
    int b = 20;
    float c = 5.2;
    float d =  2.4;
    std::string str1 = "test";
    std::string str2 = "test2";

    std::cout << "add1(a, b) = " << add1(a, b) << "\n";
    std::cout << "add1(a, c) = " << add1(a, c) << "\n";
    std::cout << "add1(c, d) = " << add1(c, d) << "\n";
    std::cout << "add1(str1, str2) = " << add1(str1, str2) << "\n";

    auto lambda = [](int a, int b) { return a + b; };
    std::cout << "add2(a, b) = " << add2(a, b, &addInt) << "\n";
    std::cout << "add2(str1, str2) = " << add2(str1, str2, &addString) << "\n";
    std::cout << "add2(a, b) = " << add2(a, b, +lambda);
    
    return 0;
}
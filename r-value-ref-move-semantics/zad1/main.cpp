#include "a.hpp"
#include <vector>

A copy(A const& obj)
{
    return A(obj);
}

A copy (A&& obj)
{
    return A(std::move(obj));
}

template<class T>
A copy(T&& obj)
{
    return A(std::forward<T>(obj));
}

int main()
{
    std::vector<A> testVec;

    A test1 = A("test");
    std::cout << test1.get() << "\n";
    A test2 = A(test1);
    std::cout << test2.get() << "\n";
    A test3 = A(std::move(test2));
    std::cout << test3.get() << "\n";

    A test4("zad9");
    std::cout << test4.get() << "\n";
    A test5 = copy(test4);
    std::cout << test5.get() << "\n";
    A test6 = copy(std::move(test4));
    std::cout << test6.get() << "\n";

    return 0;
}
#include <iostream>

template<typename T, typename ...Args>
auto add(T first, Args... args)
{
    if constexpr(sizeof...(args) == 0)
        return first;
    else
        return first + add(args...);
}


int main()
{
    std::cout << add(1.3, 3.4, 0.4f) << "\n";
    std::cout << add(1.3, 0.4f) << "\n";
    std::cout << add(1.3, 3.4, 0.4f, 0.2, 0.1f, 0.3f) << "\n";

    return 0;
}
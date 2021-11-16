#include "a.hpp"
#include <vector>

int main()
{
    std::vector<A> testVec;

    A test1 = A("test");
    A test2 = A("test2");
    A test3 = test2;

    testVec.push_back(A("vector"));
    testVec.push_back(A("vector2"));

    // testVec.insert(testVec.begin() + 1, A("newvector3"));
}
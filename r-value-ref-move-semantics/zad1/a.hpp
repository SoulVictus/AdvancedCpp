#include <string>
#include <cstring>

class A
{
    char* text;

    A(std::string const& str)
    {
        text = new char[str.size() + 1];
        std::strcpy(text, str.c_str());
    }

    A(const A& str)
    {
        std::size_t size = sizeof(str);
        text = new char[size + 1];
        std::strcpy(text, str.text);
    }

    A(A&& str)
    {
        text = str.text;
        str.text = nullptr;
    }

    ~A()
    {
        delete text;
    }

    char* get()
    {
       return text; 
    }
};
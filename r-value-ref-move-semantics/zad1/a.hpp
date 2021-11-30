#include <string>
#include <cstring>
#include <iostream>

class A
{
private:
    char* text;
    size_t size;
public:

    A(std::string const& str)
    {
        size = str.size();
        text = new char[size + 1];
        std::strcpy(text, str.c_str());
        std::cout << "main constructor" << "\n";
    }

    A(const A& obj)
    {
        size = obj.size;
        text = new char[size + 1];
        for (size_t i = 0; i < size; i++)
        {
            text[i] = obj.text[i];
        }
        text[size+1] = '\0';
        std::cout << "copy constructor" << "\n";
    }

    A(A&& obj)
    {
        text = obj.text;
        size = obj.size;
        obj.text = nullptr;
        obj.size = 0;
        std::cout << "move constructor" << "\n";
    }

    A& operator=(A&& obj)
    {
        if (this != &obj)
        {
            delete text;

            text = obj.text;
            size = obj.size;

            obj.text = nullptr;
            obj.size = 0;

            return *this;   
        }
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
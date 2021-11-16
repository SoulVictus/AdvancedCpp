#include <string>
#include <cstring>
#include <iostream>

class A
{
private:
    char* text;
    int length;
public:

    A(std::string const& str)
    {
        text = new char[str.size() + 1];
        length = str.size()+1;
        std::strcpy(text, str.c_str());
        std::cout << "main constructor" << "\n";
    }

    A(const A& obj)
    {
        std::size_t size = sizeof(obj);
        text = new char[size + 1];
        length = obj.length;
        std::strcpy(text, obj.text);
        std::cout << "copy constructor" << "\n";
    }

    A(A&& obj)
    {
        text = obj.text;
        length = obj.length;
        obj.text = nullptr;
        obj.length = 0;
        std::cout << "move constructor" << "\n";
    }

    A& operator=(A&& obj)
    {
        if (this != &obj)
        {
            delete text;

            text = obj.text;
            length = obj.length;

            obj.text = nullptr;
            obj.length = 0;

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
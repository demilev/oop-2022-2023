#include <iostream>

class A
{
public:
    int x;

    A()
    {
        x = 0;
        std::cout << "Default constructor is called" << std::endl;
    }

    A(int x)
    {
        this->x = x;
        std::cout << "Non-default constructor is called" << std::endl;
    }

    A(const A &other)
    {
        std::cout << "copy constructor is called" << std::endl;
        this->x = other.x;
    }

    A &operator=(const A &other)
    {
        std::cout << "Operator = is called" << std::endl;
        this->x = other.x;
        return *this;
    }
};

class B
{
public:
    A a;

    B(A a) // : a(a)
    {
        this->a = a;
    }
};

int main()
{
    B b(A(3));
    return 0;
}
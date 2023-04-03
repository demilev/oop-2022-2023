#include <iostream>

/*
    Примерни класове, които илюстрират използването на инициализиращи списъци и смисъла от тях.
*/
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

    // Експериментирайте с двата варианта - присвояване на стойност на a в инициализиращ и списък и в тялото на конструктора.
    // Функционално и двата подхода достигат до еднакъв резултат. Единият обаче е по-оптимален. Кой?
    B(A x) : a(x)
    {
        // this->a = x;
    }
};

int main()
{
    B b(A(3));
    return 0;
}
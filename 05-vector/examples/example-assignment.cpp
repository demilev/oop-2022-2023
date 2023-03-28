#include <iostream>

class Number
{
public:
    int x;

    Number()
    {
        this->x = 0;
    }

    Number(const Number &other)
    {
        std::cout << "Copy constructor is called" << std::endl;
        this->x = other.x;
    }

    ~Number()
    {
        std::cout << "Destructor is called" << std::endl;
    }

    Number operator=(const Number &other)
    {
        if (this != &other)
        {
            this->x = other.x;
        }

        return *this;
    }
};

int main()
{
    Number n1, n2, n3;

    n1 = n2 = n3;
    return 0;
}
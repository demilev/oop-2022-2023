#include <iostream>

class Number
{
public:
    int x;

    Number()
    {
        this->x = 0;
    }

    Number(int n)
    {
        this->x = n;
    }

    void print()
    {
        std::cout << x;
    }

    Number operator+(Number other)
    {
        return Number(x + other.x);
    }
};

int main()
{
    int a = 3;
    int b = 4;

    Number n1(4), n2(5), n3;

    n3.print();
    return 0;
}
#include <iostream>

/*
    Примерен клас, който илюстрира разликата между това да връщаме референция и копие на обекта в оператор =
*/

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

    // Експериментирайте и вижте какво става, когато връщаме копие и референция
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

    // Тази конструкция ще работи независимо от това дали връщаме копие или референция, но едно двете е по-оптимално. Кое?
    n1 = n2 = n3;
    return 0;
}
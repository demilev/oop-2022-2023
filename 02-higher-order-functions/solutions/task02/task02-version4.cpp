#include <iostream>

// Шаблонен псевдоним на тип за указател към фунцкия, която приема един параметър от шаблонния тип и връща double
template <typename T>
using Func = double (*)(T);

// Шаблонна функция, която приема елемент и две функции и която връща коя от двете функции имат по-висока стойност в точката
template <typename T>
double greater(T element, Func<T> f, Func<T> h)
{
    return f(element) - h(element);
}

// Шаблонна функция, която приема елемент и две функции и която връща по-голямата от двете функции
template <typename T>
Func<T> greaterF(T element, Func<T> f, Func<T> h)
{
    if (greater(element, f, h) < 0)
    {
        return h;
    }

    return f;
}

double square(int x)
{
    return x * x;
}

double cube(int x)
{
    return x * x * x;
}

int main()
{

    if (greater<int>(5, square, cube) < 0)
    {
        std::cout << "cube is greater than square" << std::endl;
    }
    else
    {
        std::cout << "cube is less than or equal to square" << std::endl;
    }
    Func<int> gf = greaterF<int>(5, square, cube);
    std::cout << "The value of the greater function in point 10 is: " << gf(10) << std::endl;

    return 0;
}
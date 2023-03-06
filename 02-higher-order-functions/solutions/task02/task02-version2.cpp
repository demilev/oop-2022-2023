#include <iostream>

using Func = double (*)(int);

// Функция, която приема параметър от тип int и две функции, които приемат int и връщат double
double greater(int element, Func f, Func h)
{
    return f(element) - h(element);
}

// Функция, която приема параметър от тип int и две функции, които приемат int и връщат double, и която връща по-голямата от двете функции
Func greaterF(int element, Func f, Func h)
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

    if (greater(5, square, cube) < 0)
    {
        std::cout << "cube is greater than square" << std::endl;
    }
    else
    {
        std::cout << "cube is less than or equal to square" << std::endl;
    }

    Func gf = greaterF(5, square, cube);
    std::cout << "The value of the greater function in point 10 is: " << gf(10) << std::endl;

    return 0;
}
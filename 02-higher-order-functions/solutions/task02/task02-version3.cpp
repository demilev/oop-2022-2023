#include <iostream>

// Шаблонна функция, която приема елемент и две функции и която връща коя от двете функции имат по-висока стойност в точката
template <typename T>
double greater(T element, double (*f)(T), double (*h)(T))
{
    return f(element) - h(element);
}

/* Реализация на първата подточка с този подход няма! */

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

    return 0;
}
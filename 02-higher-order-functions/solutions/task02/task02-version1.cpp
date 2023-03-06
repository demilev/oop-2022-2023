#include <iostream>


// Функция, която приема параметър от тип int и две функции, които приемат int и връщат double
double greater(int element, double (*f)(int), double (*h)(int))
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

    if (greater(5, square, cube) < 0)
    {
        std::cout << "cube is greater than square" << std::endl;
    }
    else
    {
        std::cout << "cube is less than or equal to square" << std::endl;
    }

    return 0;
}
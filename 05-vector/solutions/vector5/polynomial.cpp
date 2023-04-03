#include <iostream>
#include "polynomial.h"

Polynomial::Polynomial() : coef() {}

double Polynomial::calculate(double x)
{
    double result = 0;
    double currentPower = 1;
    for (int i = 0; i < coef.getSize(); i++)
    {
        result += coef.get(i) * currentPower;
        currentPower *= x;
    }

    return result;
}

double Polynomial::operator()(double x)
{
    return calculate(x);
}

void Polynomial::print()
{
    for (int i = 0; i < coef.getSize(); i++)
    {
        std::cout << coef.get(i) << " ";
    }

    std::cout << std::endl;
}

void Polynomial::addCoef(double c)
{
    coef.add(c);
}

void Polynomial::removeCoef()
{
    coef.remove();
}

Polynomial Polynomial::operator+(const Polynomial &other)
{   
    int maxPower = std::max(coef.getSize(), other.coef.getSize());
    int minPower = std::min(coef.getSize(), other.coef.getSize());
    Polynomial result; // Създаваме полином, в който ще трупаме резултата

    // Добавяме сумата на коефициентите, докато стигнем по-малката от двете степени
    for (int i = 0; i <= minPower; i++)
    {
        result.addCoef(other.coef.get(i) + coef.get(i));
    }

    // Добавяме останалите коефициенти на полинома от по-голяма степен
    if (other.coef.getSize() < coef.getSize())
    {
        for (int i = minPower + 1; i <= maxPower; i++)
        {
            result.addCoef(coef.get(i));
        }
    }
    else
    {
        for (int i = minPower + 1; i <= maxPower; i++)
        {
            result.addCoef(other.coef.get(i));
        }
    }

    return result;
}

#include <iostream>
#include "polynomial.h"

Polynomial::Polynomial() : power(-1), coef() {}

double Polynomial::calculate(double x)
{
    double result = 0;
    double currentPower = 1;
    for (int i = 0; i <= power; i++)
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
    for (int i = 0; i <= power; i++)
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
    int maxPower = std::max(power, other.power);
    int minPower = std::min(power, other.power);
    Polynomial result; // Създаваме полином, в който ще трупаме резултата

    // Добавяме сумата на коефициентите, докато стигнем по-малката от двете степени
    for (int i = 0; i <= minPower; i++)
    {
        result.addCoef(other.coef.get(i) + coef.get(i));
    }

    // Добавяме останалите коефициенти на полинома от по-голяма степен
    if (other.power < power)
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

#pragma once

#include "vector.h"

class Polynomial
{
private:
    int power;
    Vector<double> coef;

public:
    Polynomial();

    double calculate(double);

    double operator()(double);

    void print();

    void addCoef(double);

    void removeCoef();

    Polynomial operator+(const Polynomial &);
};

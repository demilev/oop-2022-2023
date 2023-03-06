#include <iostream>

// Две прости примерни функции
int add5(int x)
{
    return x + 5;
}

int add6(int x)
{
    return x + 6;
}

// Псевдоним на тип. Компилаторът ще замине всяко срещане на Operation с int (*)(int)
using Operation = int (*)(int);

// Функция, която приема променлива от тип int и указтел към функция,
// която приема параметър от тип int и връща резултат от тип int
void printResult(int x, Operation f)
{
    std::cout << f(x);
}

// Функция, която връща указател към функция, която приема параметър от тип int и връща резултат от тип int
Operation returnFunc()
{
    return add6;
}

int main()
{
    // Дефинираме указател към функция
    int (*f)(int);
    // Насочваме го към съществуващата фунцкия add5
    f = add5;
    // Извикваме функцията, към която сочи f
    std::cout << f(3) << std::endl;

    // Използваме псевдонима Operation. returnFunc ще върне указател към функция
    Operation h = returnFunc();

    // Подаваме този указател към printResult функция
    printResult(3, h);

    return 0;
}
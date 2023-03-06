#include <iostream>

/*
    Напишете програма, която чете две числа от стандартния вход и математичска операция(+, -, *, /), която да бъде извършена върху тях.
    За целта напишете функция, която приема `char` и връща указател към функция, която трябва да бъде приложена върху двете числа.
*/

// Използваме псевдоним към типа указател към функция, която приема два int-а и връща int.
// Често ще ползваме псевдоними, когато работим с указатели към функции, за да подобрим
// четимостта и разбираемостта на нашата програма.
using Operation = int (*)(int, int);

// Четирите прости операции дефинирани чрез функции
int plus(int x, int y)
{
    return x + y;
}

int minus(int x, int y)
{
    return x - y;
}

int product(int x, int y)
{
    return x * y;
}

int division(int x, int y)
{
    return x / y;
}

// Функция, която по въведено символче, връща операцията, която трябва да бъде приложена
Operation resolveOperation(char op)
{
    switch (op)
    {
    case '+':
        return plus;
    case '-':
        return minus;
    case '*':
        return product;
    case '/':
        return division;
    }

    // Ако не разпознаем символа, връщаме нулев указател
    return nullptr;
}

int main()
{

    int x, y;
    char op;
    std::cin >> x >> y >> op;

    Operation operation = resolveOperation(op);
    if (operation)
    {
        // Изпълняваме операцията върху входните данни
        std::cout << operation(x, y);
    }
    return 0;
}
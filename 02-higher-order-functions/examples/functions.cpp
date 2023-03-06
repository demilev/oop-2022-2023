#include <iostream>

/*
    Няколко примера на прости функции, към които насочваме указатели в main функцията.
*/

int f1() { return 5; }

double f2(double x1, double x2) { return x1 + x2; }

void f3(char c) { std::cout << c; }

int f4() { return 6; }

int f5(double x1, char x2) { return 3; }

int *f6(int x) { return nullptr; }

int main()
{
    // Указател към функция, която приема параметър от тип double и параметър от тип char и която връща int
    int (*a)(double, char);
    // Указател към функция, която приема параметър от тип int и която връща указтел към int
    int *(*b)(int);
    // Указател към функция, която не приема параметри и която връща int
    int (*c)();
    // Указател към функция, която приема параметър от тип char и която не връща резултат(void)
    void (*d)(char);
    // Указател към функция, която приема параметър от тип double и параметър от тип double и която връща double
    double (*f)(double, double);

    a = f5;
    b = f6;
    c = f4;
    c = f1;
    d = f3;
    f = f2;

    return 0;
}
#include <iostream>

class A
{
public:
    int i;

    A(int i) : i(i) {}

    ~A()
    {
        std::cout << "Object " << i << " is being destroyed" << std::endl;
    }
};

void f1()
{
    A a(1); // Тествайте какво ще стане, когато е заделена памет в хийпа - A *a = new A(1);
    std::cout << "f1() Start" << std::endl;
    throw 100; // хвърляме грешка
    // Всичко след грешката няма да бъде изпълнено, функцията ще приключи и паметта
    // заделена на стека ще бъде освободена, т.е. деструкторът на променливата "a" ще бъде извикан
    std::cout << "f1() End " << std::endl;
}

void f2()
{
    A a(2);
    std::cout << "f2() Start " << std::endl;
    f1(); // f1 хвърля грешка, която не се обработва в f2, т.е. с f2 ще стане същото като с f1
    std::cout << "f2() End " << std::endl;
}

void f3()
{
    A a(3);
    std::cout << "f3() Start " << std::endl;
    try
    {
        // f3 извиква f2 в try блок
        f2();
    }
    catch (int i)
    {
        // Грешката възниква и ще бъде обработена
        std::cout << "Caught Exception: " << i << std::endl;
    }

    // f3 продължава нормално изпълнението си
    std::cout << "f3() End" << std::endl;
}

int main()
{
    f3();
    return 0;
}

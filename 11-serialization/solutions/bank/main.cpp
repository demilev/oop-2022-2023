#include <iostream>
#include <fstream>

#include "bank.h"

int main()
{
    // Създаваме акаунт
    BankProfile bp;

    DepositAccount da(10, 1, 0.05);
    bp.addAccount(&da);

    SavingsAccount sa(10, 0.05);
    bp.addAccount(&sa);

    std::ofstream out;
    out.open("bank.txt");

    // Записваме го във файл
    out << bp;

    out.close();

    BankProfile bp1;

    std::ifstream in;
    in.open("bank.txt");

    // Прочитаме съдържанието на файла в друг акаунт
    in >> bp1;

    in.close();

    // Отпечатваме на стандартния изход дргуия акаунт.
    // Той трябва да е същият, с който сме започнали.
    std::cout << bp1;

    return 0;
}
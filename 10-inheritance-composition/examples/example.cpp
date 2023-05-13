
#include <iostream>

#include "bank.h"

int main()
{
    BankProfile bp;

    BankAccount ba(10);

    bp.addAccount(&ba);


    // Проблем 1
    {
        BankAccount ba1(11);
        bp.addAccount(&ba1);
    }

    // Проблем 2
    ba.deposit(10);


    std::string s = "abc";

    std::cout << s << " ";

    std::string copyS = s;

    std::string concat = s + copyS;



    return 0;
}

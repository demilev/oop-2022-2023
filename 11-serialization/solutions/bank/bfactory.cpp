#include "bfactory.h"

BankAccount *factory(std::string objectType)
{   
    // Създаваме обекти на базата на името, което сме ползвали да кодираме типа им.
    // Забележете, че функцията връща обекти в динамичната памет. Този, който я извиква,
    // ще трябва да се погрижи за почистването на тази памет.
    if (objectType == "depositaccount")
    {
        return new DepositAccount(0, 0, 0);
    }

    if (objectType == "savingsaccount")
    {
        return new SavingsAccount(0, 0);
    }

    if (objectType == "bankaccount")
    {
        return new BankAccount(0);
    }

    if (objectType == "paymentaccount")
    {
        return new PaymentAccount(0, 0);
    }

    // Ако името на типа не е познато връщаме нулев указател.
    // Има ли нещо по-добро, което можем да направим вместо да връщаме нулев указател?
    return nullptr;
}
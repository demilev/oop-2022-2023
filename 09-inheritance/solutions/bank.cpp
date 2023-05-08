
#include "bank.h"
#include <iostream>

BankAccount::BankAccount() : BankAccount(0) {}

BankAccount::BankAccount(int id) : id(id), balance(0) {}

void BankAccount::deposit(double money)
{
    balance += money;
}

void BankAccount::withdraw(double money)
{
    if (balance >= money)
        balance -= money;
}

double BankAccount::getBalance()
{
    return balance;
}

int BankAccount::getId()
{
    return id;
}

void BankAccount::printDetails()
{
    std::cout << "Bank Account " << id << " , Balance " << balance << std::endl;
}

// В инициализиращия списък използваме конструктора с един параметър на базовия клас.
// В противен случай ще бъде изпозлван този по подразбиране.
PaymentAccount::PaymentAccount(int id, double maxOverdraft) : BankAccount(id), maxOverdraft(maxOverdraft) {}

void PaymentAccount::withdraw(double money)
{
    if (balance + maxOverdraft >= money)
    {
        balance -= money;
    }
}

void PaymentAccount::printDetails()
{
    // Извикваме метод на базовия клас
    BankAccount::printDetails();
    std::cout << "Max overdraft " << maxOverdraft << std::endl;
}

SavingsAccount::SavingsAccount(int id, double percentReturn) : BankAccount(id), percentReturn(percentReturn) {}

void SavingsAccount::deposit(double money)
{
    balance += money;
    balance *= (1 + percentReturn);
}

void SavingsAccount::printDetails()
{
    BankAccount::printDetails();
    std::cout << "Percent return " << percentReturn << std::endl;
}

DepositAccount::DepositAccount(int id, double fee, double percentReturn) : BankAccount(id), fee(fee), percentReturn(percentReturn) {}

void DepositAccount::deposit(double money)
{
    balance += money;
    balance *= (1 + percentReturn);
}

void DepositAccount::withdraw(double money)
{
    if (balance >= (money + fee))
    {
        balance -= money;
        balance -= fee;
    }
}

void DepositAccount::printDetails()
{
    BankAccount::printDetails();
    std::cout << "Percent return " << percentReturn << ", Fee " << fee << std::endl;
}

void BankProfile::addAccount(BankAccount *account)
{
    accounts.add(account);
}

void BankProfile::deposit(int id, double money)
{
    getAccount(id)->deposit(money);
}

BankAccount *BankProfile::getAccount(int id)
{
    // Използваме метода find за търсене, подавайки ламбда функция.
    // Кодът става експресивен - в масива accounts търсим елемент, чието id съвпада с това, което сме подали
    // на метода getAccount
    int index = accounts.find([id](BankAccount *account) -> bool { return account->getId() == id; });

    return accounts.get(index);
}

void BankProfile::removeAccount(int id)
{
    int index = accounts.find([id](BankAccount *account) -> bool { return account->getId() == id; });

    return accounts.removeAtIndex(index);
}

void BankProfile::withdraw(int id, double money)
{
    getAccount(id)->withdraw(money);
}

void BankProfile::printDetails(int id)
{
    getAccount(id)->printDetails();
}

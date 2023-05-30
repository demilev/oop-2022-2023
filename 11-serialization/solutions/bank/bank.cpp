
#include "bank.h"
#include "bfactory.h"
#include <iostream>

BankAccount::BankAccount() : BankAccount(0) {}

BankAccount::BankAccount(int id) : BankAccount(0, 0) {}

BankAccount::BankAccount(int id, double balance) : id(id), balance(balance) {}

BankAccount *BankAccount::clone()
{
    return new BankAccount(id, balance);
}

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

void BankAccount::write(std::ostream &out)
{
    out << "bankaccount " << id << " " << balance << " ";
}

void BankAccount::read(std::istream &in)
{
    in >> id >> balance;
}

PaymentAccount::PaymentAccount(int id, double maxOverdraft) : BankAccount(id), maxOverdraft(maxOverdraft) {}
PaymentAccount::PaymentAccount(int id, double balance, double maxOverdraft) : BankAccount(id, balance), maxOverdraft(maxOverdraft) {}

BankAccount *PaymentAccount::clone()
{
    return new PaymentAccount(id, balance, maxOverdraft);
}

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

void PaymentAccount::write(std::ostream &out)
{
    out << "paymentaccount " << getId() << " " << balance << " " << maxOverdraft << " ";
}

void PaymentAccount::read(std::istream &in)
{
    in >> id >> balance >> maxOverdraft;
}

SavingsAccount::SavingsAccount(int id, double percentReturn) : BankAccount(id), percentReturn(percentReturn) {}
SavingsAccount::SavingsAccount(int id, double balance, double percentReturn) : BankAccount(id, balance), percentReturn(percentReturn) {}

BankAccount *SavingsAccount::clone()
{
    return new SavingsAccount(id, balance, percentReturn);
}

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

void SavingsAccount::write(std::ostream &out)
{
    out << "savingsaccount " << getId() << " " << balance << " " << percentReturn << " ";
}

void SavingsAccount::read(std::istream &in)
{
    in >> id >> balance >> percentReturn;
}

DepositAccount::DepositAccount(int id, double fee, double percentReturn) : BankAccount(id), fee(fee), percentReturn(percentReturn) {}
DepositAccount::DepositAccount(int id, double balance, double fee, double percentReturn) : BankAccount(id, balance), fee(fee), percentReturn(percentReturn) {}

BankAccount *DepositAccount::clone()
{
    return new DepositAccount(id, balance, fee, percentReturn);
}

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

void DepositAccount::write(std::ostream &out)
{
    out << "depositaccount " << getId() << " " << balance << " " << percentReturn << " " << fee << " ";
}

void DepositAccount::read(std::istream &in)
{
    in >> id >> balance >> percentReturn >> fee;
}

void BankProfile::cleanup()
{
    for (BankAccount *account : accounts)
    {
        delete account;
    }

    accounts = Vector<BankAccount *>();
}

void BankProfile::copy(const BankProfile &other)
{
    for (BankAccount *account : other.accounts)
    {
        addAccount(account);
    }
}

BankProfile::BankProfile() {}

BankProfile::BankProfile(const BankProfile &other)
{
    copy(other);
}

BankProfile::~BankProfile()
{
    cleanup();
}

BankProfile &BankProfile::operator=(const BankProfile &other)
{
    if (this != &other)
    {
        cleanup();
        copy(other);
    }

    return *this;
}

void BankProfile::addAccount(BankAccount *account)
{
    accounts.add(account->clone());
}

void BankProfile::deposit(int id, double money)
{
    getAccount(id)->deposit(money);
}

BankAccount *BankProfile::getAccount(int id)
{
    int index = accounts.find([id](BankAccount *account) -> bool
                              { return account->getId() == id; });

    return accounts.get(index);
}

void BankProfile::removeAccount(int id)
{
    int index = accounts.find([id](BankAccount *account) -> bool
                              { return account->getId() == id; });

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

std::ostream &operator<<(std::ostream &out, const BankProfile &bp)
{

    for (int i = 0; i < bp.accounts.getSize(); i++)
    {
        // Обхождаме списъка от сметки и всяка една от тях записваме във файла
        BankAccount *current = bp.accounts.get(i);
        current->write(out);
    }

    return out;
}

std::istream &operator>>(std::istream &in, BankProfile &bp)
{
    BankProfile result;
    std::string objectType;
    // Четем от файла, докато има банкови сметки
    while (in >> objectType)
    {
        // Създаваме сметката на база на типа й
        BankAccount *ba = factory(objectType);
        // Прочитаме член данните й
        ba->read(in);
        // Добавяме я към резултата
        result.addAccount(ba);
        // Освобождаваме паметта, заделена от фабриката
        delete ba;
    }

    bp = result;

    return in;
}
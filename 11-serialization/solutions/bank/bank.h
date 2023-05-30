#pragma once

#include "../../../lib/vector.h"
#include <fstream>

class BankAccount
{
protected:
    int id;
    double balance;

public:
    BankAccount();
    BankAccount(int);
    BankAccount(int, double);
    virtual ~BankAccount() = default;

    virtual BankAccount *clone();
    virtual void deposit(double);
    virtual void withdraw(double);
    // Два виртуални метода за четенето и писането на състоянието на обекта във файл
    virtual void write(std::ostream &);
    virtual void read(std::istream &);

    double getBalance();
    int getId();

    virtual void printDetails();
};

class PaymentAccount : public BankAccount
{
private:
    double maxOverdraft;

public:
    PaymentAccount(int, double);
    PaymentAccount(int, double, double);
    BankAccount *clone();
    void withdraw(double);
    void printDetails();
    void write(std::ostream &);
    void read(std::istream &);
};

class SavingsAccount : public BankAccount
{
private:
    double percentReturn;

public:
    SavingsAccount(int, double);
    SavingsAccount(int, double, double);
    BankAccount *clone();
    void deposit(double);
    void printDetails();
    void write(std::ostream &);
    void read(std::istream &);
};

class DepositAccount : public BankAccount
{
private:
    double percentReturn;
    double fee;

public:
    DepositAccount(int, double, double);
    DepositAccount(int, double, double, double);
    BankAccount *clone();
    void deposit(double);
    void withdraw(double);
    void printDetails();
    void write(std::ostream &);
    void read(std::istream &);
};

class BankProfile
{
private:
    Vector<BankAccount *> accounts;
    void cleanup();
    void copy(const BankProfile&);

public:
    BankProfile();
    BankProfile(const BankProfile &);
    ~BankProfile();
    BankProfile &operator=(const BankProfile &);

    void addAccount(BankAccount *);
    void deposit(int, double);
    BankAccount *getAccount(int);
    void removeAccount(int);
    void withdraw(int, double);
    void printDetails(int);

    // friend функция за записване на акаунта в поток.
    friend std::ostream &operator<<(std::ostream &, const BankProfile &);
};

// Функция за прочитане на акаунта от поток. Подаваме акаунта по референция, защото искаме да върнем като резултат самия поток.
std::istream &operator>>(std::istream &, BankProfile &);
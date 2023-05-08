#pragma once

#include "../../lib/vector.h"

// Базовият клас, представящ банкова сметка
class BankAccount
{
private:
    // Член данна за номер на сметката
    int id;

protected:
    // Член данна за баланса на сметката. Слагаме я в protected секцията, защото ще искаме да я достъпваме в класовете наследници
    double balance;

public:
    BankAccount();
    BankAccount(int);

    // Два виртуални метода, защото различните типове сметки ще имат различни правила за теглене и депозиране
    virtual void deposit(double);
    virtual void withdraw(double);
    
    double getBalance();
    int getId();
    
    virtual void printDetails();
};


// Клас за разплащателна сметка
class PaymentAccount : public BankAccount
{
private:
    // Допълнителна член данна
    double maxOverdraft;

public:
    PaymentAccount(int, double);
    void withdraw(double);
    void printDetails();
};

// Клас за спестовна сметка
class SavingsAccount : public BankAccount
{
private:
    double percentReturn;

public:
    SavingsAccount(int, double);
    void deposit(double);
    void printDetails();
};

// Клас за депозитна сметка
class DepositAccount : public BankAccount
{
private:
    double percentReturn;
    double fee;

public:
    DepositAccount(int, double, double);
    void deposit(double);
    void withdraw(double);
    void printDetails();
};

// Клас, представящ банков профил
class BankProfile
{
private:
    // В профила имаме списък от банкови сметки. Използваме нашия клас Vector, защото той ни предоставя 
    // много функционалност за работа с динамична колекция от обекти.
    // Забележете, че работим с указатели към базовия клас
    Vector<BankAccount *> accounts;

public:
    void addAccount(BankAccount *);
    void deposit(int, double);
    BankAccount * getAccount(int);
    void removeAccount(int);
    void withdraw(int, double);
    void printDetails(int);
};
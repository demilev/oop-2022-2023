#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../lib/doctest.h"
#include "bank.h"

// Тест за създаване на банкова сметка
TEST_CASE("testing the creation of a bank account")
{
    // Създаваме банковата сметка
    BankAccount ba(10);

    // Проверяваме, че в началото сметката е празна и че id-то е това, което сме подали в конструктора
    CHECK(ba.getBalance() == 0);
    CHECK(ba.getId() == 10);
}

// Тест за депозиране в банкова сметка
TEST_CASE("testing the deposit in a bank account")
{
    // Създаваме банковата сметка
    BankAccount ba(10);

    // Депозираме 100лв
    ba.deposit(100);

    // Проверяваме, че балансът е 100лв
    CHECK(ba.getBalance() == 100);
}

// Тест за теглене от банкова сметка
TEST_CASE("testing the withdraw from a bank account")
{
    // Създаваме банковата сметка
    BankAccount ba(10);

    // Депозираме 100лв
    ba.deposit(100);

    // Теглим 50лв
    ba.withdraw(50);

    // Проверяваме, че балансът е 50лв
    CHECK(ba.getBalance() == 50);
}

// Тест за теглене от разплащателна сметка
TEST_CASE("testing the withdraw from a payment account")
{
    // Създаваме разплащателна сметка
    PaymentAccount pa(10, 20);

    // Депозираме 100лв
    pa.deposit(100);

    // Теглим 110лв
    pa.withdraw(110);

    // Проверяваме, че балансът е -10лв и че тегленето е било успешно, въпреки че надхвърля баланса
    CHECK(pa.getBalance() == -10);
}

// Тест за депозиране в спестовна сметка
TEST_CASE("testing the deposit in a saving account")
{
    // Създаваме спестовна сметка
    SavingsAccount sa(10, 0.05);

    // Депозираме 100лв
    sa.deposit(100);

    // Проверяваме, че балансът е 105лв
    CHECK(sa.getBalance() == 105);
}

// Тест за добавяне на сметка в акаунт
TEST_CASE("testing adding a bank account in a profile")
{
    // Създаваме банков акаунт
    BankProfile bp;

    // Създаваме сметка
    PaymentAccount pa(10, 20);
    pa.deposit(100);

    // Добавяме я в акаунта
    bp.addAccount(&pa);

    // Проверяваме, че действително е добавена
    CHECK(bp.getAccount(10)->getBalance() == 100);
}

// Тест за депозиране в сметка на акаунт
TEST_CASE("testing depositing to a bank account in a profile")
{
    // Създаваме банков акаунт
    BankProfile bp;

    // Създаваме сметка
    PaymentAccount pa(10, 20);
    pa.deposit(100);

    // Добавяме я в акаунта
    bp.addAccount(&pa);

    // Депозираме през акаунта
    bp.deposit(10, 50);

    // Проверяваме, че депозитът е бил успешен
    CHECK(bp.getAccount(10)->getBalance() == 150);
}

// Тест за депозиране в спестовна сметка на акаунт
TEST_CASE("testing depositing to a savings bank account in a profile")
{
    // Създаваме банков акаунт
    BankProfile bp;

    // Създаваме сметка
    SavingsAccount sa(10, 0.05);

    // Добавяме я в акаунта
    bp.addAccount(&sa);

    // Депозираме през акаунта
    bp.deposit(10, 100);

    // Проверяваме, че депозитът е бил успешен
    CHECK(bp.getAccount(10)->getBalance() == 105);
}

// Тест за теглене от спестовна сметка на акаунт
TEST_CASE("testing withdraw of a deposit account in a profile")
{
    // Създаваме банков акаунт
    BankProfile bp;

    // Създаваме сметка
    DepositAccount da(10, 1, 0.05);

    // Добавяме я в акаунта
    bp.addAccount(&da);

    // Депозираме през акаунта
    bp.deposit(10, 100);

    // Проверяваме, че депозитът е бил успешен
    CHECK(bp.getAccount(10)->getBalance() == 105);

    // Теглим през акаунта
    bp.withdraw(10, 5);

    // Проверяваме, че тегленето е било успешно
    CHECK(bp.getAccount(10)->getBalance() == 99);
}

# Тема 9, Наследяване и виртуални функции, 02.05.2023

## Наследяване

```c++
class Vehicle
{
protected:
    int maxSpeed;
public:
    void printDetails()
    {
        std::cout << maxSpeed << std::endl;
    }
};

class Car : public Vehicle
{
private:
    int maxFuel;
};
```

## Енкапсулация при наследяване

<br/>

![Diagram](content/table-class.png)

<br/>

## Указател към базов клас

```c++
class A {};

class B : public A {};

class C : public A {};

int main()
{
    A *ptr = new B();
    
    A a;
    B b;
    C c;

    A *arr[] = {&a, &b, &c};
}
```

## Виртуални функции

```c++
class Vehicle
{
protected:
    int maxSpeed;
public:
    virtual void printDetails()
    {
        std::cout << maxSpeed << std::endl;
    }
};

class Car : public Vehicle
{
private:
    int maxFuel;
public:
    void printDetails()
    {
        std::cout <<  maxSpeed << << " " << maxFuel << std::endl;
    }
};
```

## Задачи - [Решения](./solutions/)

### Зад. 1

Да се създаде клас `BankAccount`, който представя една банкова сметка. Всяка сметка си има номер и баланс. Добавете методи:

* `void deposit(double)` за добавяне на пари към сметката
* `void withdraw(double)` за премахване на пари от сметката
* `double balance()`, който връща баланса по сметката


### Зад. 2

Добавете два класа наследника - за раплащателна сметка и за спестовна сметка. Разплащателната сметка позволява теглене на пари до определена сума над текущия баланс на сметката, а при спестовната сметка всяко депозиране добавя процент сума към текущия баланс.

### Зад. 3

Имплементирайте клас `BankProfile`, представящ банков профил. Всеки банков профил има списък от банкови сметки.

### Зад. 4

Добавете следните методи към `BankProfile`:

* `void addAccount(BankAccount *)` за добавяне на нова сметка
* `void removeAccount(int)` за премахване на сметка
* `void deposit(int, double)` за депозиране на пари по сметка
* `void withdraw(int, double)` за теглене на пари от сметка
* `void printDetails(int)`, който отпечатва на екрана детайли за сметка. За целта добавете метод `printDetails` и към класа `BankAccount`.


### Зад. 5

Добавете още един тип банкова сметка `DepositAccount`, която прилича на спестовата сметкa, но при която се начислява такса при всяко теглене.
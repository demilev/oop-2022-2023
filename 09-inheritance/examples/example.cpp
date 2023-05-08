
#include <iostream>

// Базов клас за превозно средство
class Vehicle
{
public:
    int maxSpeed;
    // виртуален метод за отпечване на детайлите
    virtual void printDetails()
    {
        std::cout << "Max speed: " << maxSpeed << std::endl;
    }
};

// Класът Car наследява класа Vehicle
class Car : public Vehicle
{
public:
    // Допълнителни член данни
    int maxFuel;
    // Имплементанцията на printDetails е различна
    void printDetails()
    {
        std::cout << "Max speed: " << maxSpeed << std::endl;
        std::cout << "Max fuel: " << maxFuel << std::endl;
    }
};

// Класът Bike наследява класа Vehicle
class Bike : public Vehicle
{
public:
    // Допълнителни член данни
    int tyreSize;

    // Имплементанцията на printDetails е различна
    void printDetails()
    {
        std::cout << "Max speed: " << maxSpeed << std::endl;
        std::cout << "Tyre size: " << tyreSize << std::endl;
    }
};

int main()
{
    // Създаваме една кола и едно колело
    Car c;
    c.maxSpeed = 220;
    c.maxFuel = 60;
    Bike b;
    b.maxSpeed = 40;
    b.tyreSize = 20;

    // Можем да създаваме указател към базовия клас, който сочи към обекти от типа наследници
    Vehicle *ptr1 = &c;
    Vehicle *ptr2 = &b;

    // Събираме ги в масив. Така на практика получаваме масив от обекти от ралзичен тип
    Vehicle *vehicles[] = {&c, &b};

    for (int i = 0; i < 2; i++)
    {
        // Извикваме виртуалния метод. За всеки обект ще се извика неговата имплементация - полиморфизъм!
        vehicles[i]->printDetails();
    }

    b.printDetails();

    return 0;
}
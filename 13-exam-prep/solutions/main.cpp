#include <iostream>
#include <vector>
#include <fstream>

#include "price.h"
#include "catalogue.h"

// Шаблонна функция за намиране на най-евтин елемент в масив
template <typename T>
T cheapest(std::vector<T> items, std::function<Pricing *(T)> getPrice)
{

    // В празния вектор няма най-евтин елемент
    if (items.size() == 0)
    {
        throw std::runtime_error("Can't find the cheapest element in an empty vector");
    }

    T minItem = items[0];

    // Обхождаме всички елементи
    for (T item : items)
    {
        // Вземаме цената на текущия елемент и на текущия най-евтин елемент
        Pricing *price = getPrice(item);
        Pricing *minPrice = getPrice(minItem);

        // Ако имат различни валути, няма как да ги сравним(15 лева не са повече от 10 евро)
        if (price->getCurrency() != minPrice->getCurrency())
        {
            throw std::runtime_error("Can't comparare prices with different currency");
        }

        if (price->getPrice() < minPrice->getPrice())
        {
            minItem = item;
        }
    }

    return minItem;
}

// Два непълни примернини класове, които ще ползваме само да визулазираме извикването на горната функция
class Book
{
private:
    Pricing *p;

public:
    Book(Pricing *p) : p(p) {}

    Pricing *getPrice() { return p; }
};

class Car
{
private:
    Pricing *p;

public:
    Car(Pricing *p) : p(p) {}

    Pricing *getPrice() { return p; }
};

int main()
{

    PayNow p1(10, "USD");
    PayLater p2(50, "USD");
    PayLater p3(30, "USD");

    try
    {
        // Масиви от коли и книги
        std::vector<Book> books = {Book(&p1), Book(&p2), Book(&p3)};
        std::vector<Car> cars = {Car(&p1), Car(&p2), Car(&p3)};

        // Намираме най-евтината книга като подаваме ламбда функция, която указва как се извлича цената за дадена книга
        Book cheapestBook = cheapest<Book>(books, [](Book b) -> Pricing *
                                           { return b.getPrice(); });
        std::cout << cheapestBook.getPrice()->getPrice() << std::endl;

        // Намираме най-евтината кола като подаваме ламбда функция, която указва как се извлича цената за дадена кола
        Car cheapestCar = cheapest<Car>(cars, [](Car c) -> Pricing *
                                        { return c.getPrice(); });
        std::cout << cheapestCar.getPrice()->getPrice() << std::endl;
    }
    catch (std::runtime_error error)
    {
        std::cout << "There was an error when finding the cheapest element: " << error.what() << std::endl;
    }

    // Създаваме каталог
    Catalogue c;

    // Добаваме му няколко продукти
    c.addProduct("1", &p1);
    c.addProduct("2", &p2);
    c.addProduct("3", &p3);

    // Записваме го във файл
    std::ofstream outFile;
    outFile.open("catalogue.txt");

    outFile << c;

    outFile.close();

    try
    {   
        // Опитваме се да прочетем съдържанието на файла
        Catalogue result;
        std::ifstream inFile;
        inFile.open("catalogue.txt");

        inFile >> result;

        inFile.close();

        // Отпечатваме резултата на екрана
        std::cout << result;
    }
    // Хващаме грешка от тип runtime_error
    catch (std::runtime_error error)
    {
        std::cout << "There was an error when reading the catalogue: " << error.what() << std::endl;
    }
    // Хващаме грешка от тип exception
    catch (std::exception error)
    {
        std::cout << "There was a generic error when reading the catalogue: " << error.what() << std::endl;
    }

    return 0;
}
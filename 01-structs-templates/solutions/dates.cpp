#include <iostream>

/*
    Зад. 1
    Дефинирайте струкутра `Date`, която описва една дата (ден, месец, година) и структура `DateRange`, която описва диапазон от дати.
    Напишете функции, които инициализират съответните структури, четейки от стандартния вход и функции, които ги отпечатват на стандартния изход.
*/

// Датата има ден, месец и година
struct Date
{
    int day;
    int month;
    int year;
};

// Диапазон от дати еднозначно се определя от начална и крайна дата
struct DateRange
{
    Date from;
    Date until;
};

// Функция, която приема една дата и я отпечатва на екрана, достъпвайки член данните й
void printDate(const Date &d)
{
    std::cout << d.day << "." << d.month << "." << d.year;
}

// Функция, която приема един диапазон от данни и която отпечатва началото и края му, извиквайки предната функция
void printDateRange(const DateRange &dr)
{
    printDate(dr.from);
    std::cout << " - ";
    printDate(dr.until);
}

// Функция, която приема една дата и прочита стойностите й от екрана.
// Забележете, че този път не подаваме параметър с const, защото ще го модифицираме.
// Вижте повече за const във файла с условия на задачите.
void readDate(Date &d)
{
    std::cin >> d.day >> d.month >> d.year;
}

// Функция, която приема един диапазон и прочита стойностите му от екрана с помощтта на предишната функция.
void readDateRange(DateRange &dr)
{
    readDate(dr.from);
    readDate(dr.until);
}

/*
    Зад. 2
    Напишете функция, която приема една дата и един диапазон от дати и която проверява дали датата принадлежи на съответния диапазон.
*/

// Помощна функция, която проверява дали една дата е преди друга дата.
bool isBefore(const Date &d1, const Date &d2)
{
    if (d1.year != d2.year)
        return d1.year < d2.year;

    if (d1.month != d2.month)
        return d1.month < d2.month;

    if (d1.day != d2.day)
        return d1.day < d2.day;

    return true;
}

// Имайки предишната помощна функция, проверката за принадлежност става елементарна.
// Една дата е в диапазона, ако е преди края му и не е преди началото му.
bool contains(const DateRange &dr, const Date &d)
{
    return isBefore(d, dr.until) && !isBefore(d, dr.from);
}

/*
    Зад. 3
    Дефинирайте струкутра `Hotel`, която описва хотел чрез името му, средната му цена за нощувка и масив от диапазони от дати,
    за които хотелът е наличен за резервации. Напишете функция, която инициализира един хотел от стандартния вход и функция,
    която отпечатва един хотел на стандартния изход.
*/

struct Hotel
{
    char name[50];
    double price;
    DateRange ranges[50];
    int rangesSize;
};

void printHotel(const Hotel &hotel)
{
    std::cout << hotel.name << std::endl;
    std::cout << hotel.price << std::endl;
    for (int i = 0; i < hotel.rangesSize; i++)
    {
        printDateRange(hotel.ranges[i]);
        std::cout << std::endl;
    }
}

void readHotel(Hotel &hotel)
{
    std::cin.ignore();
    std::cin.getline(hotel.name, 50);
    std::cin >> hotel.price >> hotel.rangesSize;
    for (int i = 0; i < hotel.rangesSize; i++)
    {
        readDateRange(hotel.ranges[i]);
    }
}

/*
    Зад. 4
    Напишете функция, която приема масив от хотели и дата и която намира броя на хотелите, които могат да бъдат резервирани на тази дата.
*/

// Помощна функция, която проверява дали един хотел е свободен за конкретна дата
bool isHotelAvailalbe(const Hotel &h, const Date &d)
{
    for (int i = 0; i < h.rangesSize; i++)
    {
        if (contains(h.ranges[i], d))
            return true;
    }

    return false;
}

// Обхождаме и броим хотелите, които са свободни за дадената дата
int freeHotels(Hotel hotels[], int size, const Date &d)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (isHotelAvailalbe(hotels[i], d))
            count++;
    }

    return count;
}

int main()
{
    // Зад. 1 и 2
    DateRange range;
    readDateRange(range);

    Date d;
    readDate(d);

    std::cout << "Range ";
    printDateRange(range);
    std::cout << " contains date ";
    printDate(d);
    std::cout << ": " << contains(range, d) << std::endl;

    // Зад. 3 и 4
    Hotel hotels[3];
    for (int i = 0; i < 3; i++)
    {
        readHotel(hotels[i]);
    }

    printHotel(hotels[0]);

    std::cout << "Number of free hotels for date ";
    printDate(d);
    std::cout << ": " << freeHotels(hotels, 3, d) << std::endl;

    return 0;
}
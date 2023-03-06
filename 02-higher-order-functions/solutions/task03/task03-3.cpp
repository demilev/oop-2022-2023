#include <iostream>

/*
    Напишете шаблон на функция, която приема масив и булево условие над елементите на масива и която брои колко от елементите на масива отговарят на условието. Изтествайте функцията, като я извикате за:
        * масив от цели числа и проверка за четност
        * масив от дати и проверка за високосност на годината на датата
*/

// Познатата структура за дата
struct Date
{
    int day;
    int month;
    int year;
};

// Същата функция като от предната подточка, но този път масивът е от елемнти от шаблонния тип и булевото условие също
template <typename T>
int countIf(T arr[], int size, bool (*f)(T))
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (f(arr[i]))
            count++;
    }

    return count;
}

bool isEven(int x)
{
    return x % 2 == 0;
}

bool isLeap(Date d)
{
    int year = d.year;
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int main()
{
    int arr[] = {1, 2, 3, 4};
    // Извикаване на фунцкията за масив от цели числа
    std::cout << countIf<int>(arr, 4, isEven) << std::endl;

    Date dates[3];
    dates[0].year = 2020;
    dates[1].year = 2022;
    dates[2].year = 2024;

    // Извикване на абсолютно същата функция, но за масив от дати!
    std::cout << countIf<Date>(dates, 3, isLeap) << std::endl;

    return 0;
}
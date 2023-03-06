#include <iostream>

/*
    Напишете шаблон на функция, която приема масив и го сортира във възходящ ред, като позволите да бъде подаван критерий за сравнение на елементите в масива.
    Изтествайте функцията, като я извикате за:
        * масив от цели числа и наредба в низходящ ред
        * масив от дати и наредба по година във възходящ ред (вижте Зад. 1 от тема 1 за структурата за дата)
*/

// Познатата структура за дата
struct Date
{
    int day;
    int month;
    int year;
};

// Selection sort - https://en.wikipedia.org/wiki/Selection_sort
template <typename T>
void sort(T arr[], int size, int (*compare)(T, T))
{
    for (int i = 0; i < size; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            // Този път ползваме условието за сравнение
            if (compare(arr[j], arr[minIndex]) < 0)
                minIndex = j;
        }

        T temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

int desc(int a, int b)
{
    return b - a;
}

int byYear(Date a, Date b)
{
    return a.year - b.year;
}

int main()
{

    int intArr[] = {3, 2, 1, 4};
    Date dateArr[3];
    dateArr[0].year = 2023;
    dateArr[1].year = 2022;
    dateArr[2].year = 2020;

    // Сортираме масив от цели числа в низходящ ред
    sort<int>(intArr, 4, desc);
    // Сортираме масив от дати по година
    sort<Date>(dateArr, 3, byYear);

    for (int i = 0; i < 4; i++)
    {
        std::cout << intArr[i] << " ";
    }

    std::cout << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << dateArr[i].year << " ";
    }

    std::cout << std::endl;
    return 0;
}
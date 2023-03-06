#include <iostream>

/*
    Напишете функция, която приема масив от цели числа и булево условие и която намира броя на елементите, които отговарят на това условие
*/

// Дефинираме булевото условие като указател към функция, която приема int и връща bool
int countIf(int arr[], int size, bool (*f)(int))
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        // Имплементацията е същата като от предишното решение, но този път проверката в if-а е извикаване на функцията
        if (f(arr[i]))
            count++;
    }

    return count;
}

bool isEven(int x)
{
    return x % 2 == 0;
}

bool isPositive(int x)
{
    return x > 0;
}

int main()
{
    int arr[] = {1, 2, 3, 4};

    // Примерно извикване с проверка за четност
    std::cout << countIf(arr, 4, isEven) << std::endl;
    // Примерно извикване с проверка за позитивност
    std::cout << countIf(arr, 4, isPositive) << std::endl;

    return 0;
}
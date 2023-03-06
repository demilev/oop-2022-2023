#include <iostream>

/*
    Напишете шаблон на функция, която приема масив и го сортира във възходящ ред.
*/

// Selection sort - https://en.wikipedia.org/wiki/Selection_sort
template <typename T>
void sort(T arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        T temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

int main()
{

    int intArr[] = {3, 2, 1, 4};
    double doubleArr[] = {1.5, 0.3, -2, -12};

    // Сортираме масив от цели числа
    sort<int>(intArr, 4);
    // Сортираме масив от реални числа
    sort<double>(doubleArr, 4);

    for (int i = 0; i < 4; i++)
    {
        std::cout << intArr[i] << " ";
    }

    std::cout << std::endl;

    for (int i = 0; i < 4; i++)
    {
        std::cout << doubleArr[i] << " ";
    }

    std::cout << std::endl;
    return 0;
}
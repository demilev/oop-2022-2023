#include <iostream>

/*
    Напишете функция, която намира броя на четните числа в масив от цели числа
*/

int countEvens(int arr[], int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
            count++;
    }

    return count;
}

int main()
{
    int arr[] = {1, 2, 3, 4};
    std::cout << countEvens(arr, 4) << std::endl;
    return 0;
}
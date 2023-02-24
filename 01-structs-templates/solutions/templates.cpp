#include <iostream>

/*
    Зад. 5
    Напишете шаблонна функция, която отпечатва елементите на масив.
*/

// Единственото ново е синтаксисът, който ни помага да направим функцията шаблонна.
// Имплементацията на функцията е абсолютно 1:1 с функция, която бихме написали за масив от int-ове
template <typename T>
void print(T arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return;
}

/*
    Зад. 6
    Напишете шаблонна функция, която връща индекса на най-големия елемент на масив.
*/
template <typename T>
int max(T arr[], int size)
{
    int maxIndex = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > arr[maxIndex])
            maxIndex = i;
    }

    return maxIndex;
}

// Версия на предишната функция, която в този случай връща най-големия елемент, а не индекса му.
template <typename T>
T maxElement(T arr[], int size)
{
    int maxIndex = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] > arr[maxIndex])
            maxIndex = i;
    }

    return arr[maxIndex];
}

/*
    Зад. 7
    Напишете шаблонна функция, която приема масив и елемент и проверява дали този елемент принадлежи на масива.
*/

// За разнообразие ползваме B вместо T. Реално няма значение какво ползваме, защото това просто е името на параметризирания тип.
// Забележете, че отново ползваме конструкция от типа const &.
template <typename B>
bool contains(B arr[], int size, const B &elem)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == elem)
            return true;
    }

    return false;
}

/*
    Зад. 8
    Напишете шаблонна функция, която приема масив и два елемента и която променя всички срещания на първия елемент с втория.
*/
template <typename T>
void replace(T arr[], int size, const T &find, const T &replace)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == find)
            arr[i] = replace;
    }
}

int main()
{

    int arr[] = {1, 2, 3};
    double arr1[] = {1.2, 5.3, 13.5};
    char arr2[] = {'a', 'b', 'c'};

    // Зад. 5
    print<int>(arr, 3);

    // Зад. 6
    std::cout << max<double>(arr1, 3) << std::endl;

    // Зад. 7
    std::cout << contains<char>(arr2, 3, 'b') << std::endl;

    // Зад. 8
    replace<int>(arr, 3, 2, 5);
    print<int>(arr, 3);

    return 0;
}
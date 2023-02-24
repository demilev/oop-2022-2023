#include <iostream>

// Функция, която приема int и го печата на екрана
void printInt(int a)
{
    std::cout << a;
}

// Абсолютно същата функция, но приема double
void printDouble(double a)
{
    std::cout << a;
}

// Абсолютно същата функция, но приема char
void printChar(char a)
{
    std::cout << a;
}

// За да не се налага да пишем една и съща функция за всеки тип,
// създаваме шаблон на функция. Ключовата дума template указва,
// че това ще е шаблон на функция. С typename Т казваме, че шаблонният тип
// ще се казва T. Функцията приема параметър от тип T.
template <typename T>
void print(T a)
{
    std::cout << a;
}

int main()
{
    int n = 1;
    double d = 1.5;
    char c = 'b';
    // Стандартно извикване на обикновените функции
    printInt(n);
    printDouble(d);
    printChar(c);

    // Извикваме шаблонната функция с T=int. Компилаторът ще използва шаблона, за да създаде версия на функцията, която работи с int.
    print<int>(n);
    // Същото, но за double
    print<double>(d);
    // Същото, но за char
    print<char>(c);

    int a = 3;
    const int &b = a;
    a = 5;

    return 0;
}
#include <iostream>
#include <cmath>

// Клас, описващ точка в равнината
class Point
{
public:
    // Моделираме една точка с двете й координати
    double x;
    double y;

    // Конструктор по подразбиране - използваме центъра на координатната система за точка по подразбиране
    Point()
    {
        x = 0;
        y = 0;
    }

    // Конструктор с два параметъра, които се ползват да зададат начални стойности на координатите на точката
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    // Метод за отпечатване на състоянието на точката
    void print()
    {
        std::cout << "x: " << x << ", y: " << y << std::endl;
    }

    // Метод за намиране на разстояние между две точки
    double distance(const Point &other)
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    // Предифинираме оператор - да работи като горнията функция
    double operator-(const Point &other)
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    // Оператор + за събиране на две точки. Създаваме нова такава като резултат
    Point operator+(const Point &other)
    {
        return Point(x + other.x, y + other.y);
    }

    // Оператор за умножаване на точка с число. Създаваме нова такава като резултат
    Point operator*(int n)
    {
        return Point(x * n, y * n);
    }

    // Оператор за сравняване на две точки. Две точки са равни, ако координатите им съвпадат
    bool operator==(const Point &other)
    {
        return x == other.x && y == other.y;
    }
};

// Оператор за умножаване на число с точка. Създаваме нова такава като резултат
// Това е пример, че можем да предефинираме оператори и извън класовете.
Point operator*(int n, Point p)
{
    return Point(p.x * n, p.y * n);
}

// Шаблонна функция, която проверя масив за принадлежност на елемент.
// Писахме я първата седмица и сега се вижда как можем да я преизползваме
// за масиви от новия ни тип, защото сме имплементирали оператора за сравнение.
template <typename B>
bool contains(B arr[], int size, B elem)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == elem)
            return true;
    }

    return false;
}

int main()
{
    // Създаваме няколко точки
    Point p(3, 4);
    Point p1(0, 1);
    Point p2;

    // Отпечатваме ги на екрана
    p.print();
    p1.print();

    // Тестваме метода за намиране на разстояние
    std::cout << p.distance(p1) << std::endl;

    // Използване на операторите за умножение на точка с число и число с точка
    p2 = p * 3; // Аналогично на p.operator*(3);
    p2 = 3 * p; // Аналогично на operator*(3, p);

    // Проверяваме какво е станало с p2
    p2.print();

    // Изпозлване на оператор == за нашите точки
    if (p == p1)
    {
        std::cout << "the points are equal";
    }
    else
    {
        std::cout << "the points are not equal";
    }

    Point points[3] = {p, p1, p2};

    Point p3;
    p3 = p2 * 6;

    // Извикване на шаблонната функция за масив от точки
    std::cout << contains<Point>(points, 3, p) << std::endl;
    std::cout << contains<Point>(points, 3, p3) << std::endl;
    return 0;
}
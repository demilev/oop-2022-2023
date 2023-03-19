#include <iostream>
#include <cmath>

// Ще преизползваме хубавия ни клас от предната задачата, защото ще ни помогне да моделираме класа триъгълник
class Point
{
public:
    double x;
    double y;

    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    double distance(const Point &other)
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

class Triangle
{
public:
    // Един триъгълник се дефинира чрез трите си върха
    Point x1;
    Point x2;
    Point x3;

    // В конструктура по подразбиране не правим нищо. Автоматично за нас ще бъде извикан конструктора по подразбиране на трите член данни.
    Triangle() {}

    // Конструктор с три точки, които да инициализират началното състояние на триъгълника
    Triangle(Point x1, Point x2, Point x3)
    {
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
    }

    // Конструктор с координатите на три точки, които да инициализират началното състояние на триъгълника
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        this->x1 = Point(x1, y1);
        this->x2 = Point(x2, y2);
        this->x3 = Point(x3, y3);
    }

    // Помощни функции за намиране на страните на триъгълника
    double a()
    {
        // Преизползваме метода за намиране на разстояние!
        return x1.distance(x2);
    }

    double b()
    {
        return x2.distance(x3);
    }

    double c()
    {
        return x3.distance(x1);
    }

    // Имайки помощните функции за намирането на страните, следващите две функции стават елементарни.
    double p()
    {
        return a() + b() + c();
    }

    double s()
    {
        double p2 = p() / 2;
        return sqrt(p2 * (p2 - a()) * (p2 - b()) * (p2 - c()));
    }

    // Оператор за сравнение на два триъгълника по лице
    bool operator<(Triangle &other)
    {
        return this->s() < other.s();
    }
};

// Шаблонна функция от седмица 1 за намиране на най-голям елемент в масив
template <typename T>
T maxElement(T arr[], int size)
{
    int maxIndex = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[maxIndex] < arr[i])
            maxIndex = i;
    }

    return arr[maxIndex];
}

int main()
{
    // Създаваме няколко точки
    Triangle t;
    Triangle t1(Point(0, 0), Point(1, 1), Point(5, 4));
    Triangle t2(1, 2, 3, 5, -1, 0);

    // Тестваме методите за намиране на лице и периметър
    std::cout << t1.p() << std::endl;
    std::cout << t2.s() << std::endl;

    // Намираме триъгълника с най-голямо лице
    Triangle triangles[] = {t, t1, t2};
    std::cout << maxElement(triangles, 3).s() << std::endl;
    return 0;
}
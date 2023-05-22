#include <cmath>
#include "triangle.h"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Point::distance(const Point &other) const
{
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

bool Point::operator==(const Point &other) const
{
    return this->x == other.x && this->y == other.y;
}

Triangle::Triangle() {}

Triangle::Triangle(const Point &x1, const Point &x2, const Point &x3)
{
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
}

double Triangle::a() const
{
    return x1.distance(x2);
}

double Triangle::b() const
{
    return x2.distance(x3);
}

double Triangle::c() const
{
    return x3.distance(x1);
}

double Triangle::p() const
{
    return a() + b() + c();
}

double Triangle::s() const
{
    double p2 = p() / 2;
    return sqrt(p2 * (p2 - a()) * (p2 - b()) * (p2 - c()));
}

bool Triangle::operator<(const Triangle &other) const
{
    return this->s() < other.s();
}

bool Triangle::operator==(const Triangle &other) const
{
    return this->x1 == other.x1 && this->x2 == other.x2 && this->x3 == other.x3;
}

void writeTriangle(const Triangle &triangle, std::ofstream &file)
{
    // Пишем във файла все едно пишем на стандартния изход.
    // Забележете, че в тази функция не се грижим за създаването и освобождаването на потока, защото той се подава като аргумент на функцията.
    // Този, който извиква функцията, ще се грижи за този ресурс.
    file << triangle.x1.x << " " << triangle.x1.y << " "
         << triangle.x2.x << " " << triangle.x2.y << " "
         << triangle.x3.x << " " << triangle.x3.y;
}

Triangle readTriangle(std::ifstream &file)
{
    int x1, y1, x2, y2, x3, y3;

    // Четем от файла все едно четем от стандартния вход
    // Забележете, че в тази функция не се грижим за създаването и освобождаването на потока, защото той се подава като аргумент на функцията.
    //// Този, който извиква функцията, ще се грижи за този ресурс.
    file >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    return Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3));
}

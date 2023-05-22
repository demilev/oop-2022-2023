#include <fstream>

class Point
{
public:
    double x;
    double y;

    Point();
    Point(double, double);

    double distance(const Point &) const;

    bool operator==(const Point &) const;
};

class Triangle
{
private:
    Point x1;
    Point x2;
    Point x3;
public:

    Triangle();

    Triangle(const Point&, const Point&, const Point&);

    double a() const;
    double b() const;
    double c() const;
    double p() const;
    double s() const;

    bool operator<(const Triangle &) const;

    bool operator==(const Triangle &) const;

    // friend функция за записване на триъгълник във файл.
    // friend функциите не са член функции, а са функции, които имат достъп до private данните на класа
    friend void writeTriangle(const Triangle &, std::ofstream&);
};


// Функция за четене на триъгълник от файл
Triangle readTriangle(std::ifstream&);
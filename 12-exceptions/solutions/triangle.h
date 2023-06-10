#include "csv.h"

class Point
{
public:
    double x;
    double y;

    Point();
    Point(double, double);

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

    bool operator==(const Triangle &) const;

    friend CSV toCsv(std::vector<Triangle>);
};

std::vector<Triangle> readTriangles(CSV);

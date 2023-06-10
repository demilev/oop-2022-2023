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

bool Triangle::operator==(const Triangle &other) const
{
    return this->x1 == other.x1 && this->x2 == other.x2 && this->x3 == other.x3;
}

std::vector<Triangle> readTriangles(CSV csv)
{
    return csv.as<Triangle>([](Row row) -> Triangle {
        if(row.cells.size() != 6)
        {
            throw std::runtime_error("Expected 6 columns, got " + std::to_string(row.cells.size()));
        }
        
        return Triangle(
            Point(std::stod(row.cells[0].value), std::stod(row.cells[1].value)),
            Point(std::stod(row.cells[2].value), std::stod(row.cells[3].value)),
            Point(std::stod(row.cells[4].value), std::stod(row.cells[5].value))
        ); 
    });
}

CSV toCsv(std::vector<Triangle> triangles)
{
    std::vector<Header> headers;
    headers.push_back(Header("x1", 0));
    headers.push_back(Header("y1", 1));
    headers.push_back(Header("x2", 2));
    headers.push_back(Header("y2", 3));
    headers.push_back(Header("x3", 4));
    headers.push_back(Header("y3", 5));

    std::vector<Row> rows;
    int rowNumber = 1;
    for (Triangle t : triangles)
    {
        std::vector<Cell> cells;
        cells.push_back(Cell(headers[0], std::to_string(t.x1.x)));
        cells.push_back(Cell(headers[1], std::to_string(t.x1.y)));
        cells.push_back(Cell(headers[2], std::to_string(t.x2.x)));
        cells.push_back(Cell(headers[3], std::to_string(t.x2.y)));
        cells.push_back(Cell(headers[4], std::to_string(t.x3.x)));
        cells.push_back(Cell(headers[5], std::to_string(t.x3.y)));

        rows.push_back(Row(rowNumber++, cells));
    }

    return CSV(headers, rows);
}
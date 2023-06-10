#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../lib/doctest.h"
#include "hotel.h"
#include "triangle.h"

TEST_CASE("Serialization and deserialization of a list of hotels")
{
    std::vector<Hotel> hotels;
    hotels.push_back(Hotel("1", "Test1", "Address1", 30, 30, 5));
    hotels.push_back(Hotel("2", "Test2", "Address2", 40, 20, 15));
    hotels.push_back(Hotel("3", "Test3", "Address3", -10, 55, 3));

    CSV hotelsCSV = toCsv(hotels);

    CSVWriter::write("hotels.csv", hotelsCSV);

    CSV hotelsCSVResult = CSVParser::read("hotels.csv");

    std::vector<Hotel> hotelsResult = readHotels(hotelsCSVResult);

    CHECK(hotels == hotelsResult);
}

TEST_CASE("Serialization and deserialization of a list of triangles")
{
    std::vector<Triangle> triangles;
    triangles.push_back(Triangle(Point(0, 0), Point(1, 1), Point(5, 4)));
    triangles.push_back(Triangle(Point(2, 7), Point(-5, 13), Point(14.3, 2)));
    triangles.push_back(Triangle(Point(-823, -13423), Point(112, 11321), Point(533, 0)));

    CSV trianglesCSV = toCsv(triangles);

    CSVWriter::write("triangles.csv", trianglesCSV);

    CSV trianglesCSVResult = CSVParser::read("triangles.csv");

    std::vector<Triangle> trianglesResult = readTriangles(trianglesCSVResult);

    CHECK(triangles == trianglesResult);
}

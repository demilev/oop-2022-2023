#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../lib/doctest.h"
#include "triangle.h"

// Стандартен тест, когато работим със сериализация и десериализация.
// Проверяваме, че ако сериализираме един обект във файл и след това десериализираме съръжанието на файла, получаваме оригиниалния обект
TEST_CASE("Serialization and deserialization of a triangle")
{
    Triangle t1(Point(0, 0), Point(1, 1), Point(5, 4));

    std::ofstream ofile;
    ofile.open("triangle.txt");

    writeTriangle(t1, ofile);

    ofile.close();

    std::ifstream ifile;
    ifile.open("triangle.txt");

    Triangle t2 = readTriangle(ifile);

    ifile.close();

    CHECK(t1 == t2);
}

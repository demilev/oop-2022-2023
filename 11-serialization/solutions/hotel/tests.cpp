#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../lib/doctest.h"
#include "hotel.h"

// Стандартен тест, когато работим със сериализация и десериализация.
// Проверяваме, че ако сериализираме един обект във файл и след това десериализираме съръжанието на файла, получаваме оригиниалния обект
TEST_CASE("Serialization and deserialization of a list of hotels")
{
    std::vector<Hotel> hotels;
    hotels.push_back(Hotel("1", "Test1", "Address1", 30, 30, 5));
    hotels.push_back(Hotel("2", "Test2", "Address2", 40, 20, 15));
    hotels.push_back(Hotel("3", "Test3", "Address3", -10, 55, 3));

    write(hotels, "hotels.csv");

    std::vector<Hotel> result = read("hotels.csv");

    CHECK(hotels == result);
}

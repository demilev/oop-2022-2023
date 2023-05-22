#include "hotel.h"
#include <fstream>

Hotel::Hotel() {}

Hotel::Hotel(
    const std::string &id,
    const std::string &name,
    const std::string &address,
    double x,
    double y,
    int rooms) : id(id), name(name), address(address), x(x), y(y), rooms(rooms)
{
}

bool Hotel::operator==(const Hotel &other) const
{
    return this->id == other.id && this->name == other.name &&
           this->address == other.address && this->x == other.x &&
           this->y == other.y && this->rooms == other.rooms;
}

void write(const std::vector<Hotel> &hotels, const std::string &fileName)
{
    // Грижим се за създаването на потока
    std::ofstream file;
    file.open(fileName);

    // Обхождаме хотелите
    for (const Hotel &hotel : hotels)
    {
        // Записваме по един ред за всеки хотел.
        // Член данните на хотела са разделение със запетаи
        file << hotel.id << "," << hotel.name << ","
             << hotel.address << "," << hotel.x << ","
             << hotel.y << "," << hotel.rooms;

        file << std::endl;
    }

    // Грижим се за освобождаването на потока
    file.close();
}

// Помощна функция, която разделя един string, съставен от думи разделение със запетаи, на списък от думите
std::vector<std::string> split(const std::string &s, char delimeter)
{
    std::vector<std::string> result;
    std::string current;

    // Обхождаме string-а
    for (const char &c : s)
    {
        // Ако не сме стигнали разделителния символ
        if (c != delimeter)
        {
            // Добавяме текущия символ към текущата дума
            current.push_back(c);
        }
        else
        {
            // В противен случай добавяме текущата дума към резултата и я зануляваме
            result.push_back(current);
            current = "";
        }
    }

    // Не забравяме да добавим и последната дума
    result.push_back(current);

    return result;
}

std::vector<Hotel> read(const std::string &fileName)
{
    std::vector<Hotel> result;

    // Грижим се за създаването на потока
    std::ifstream file;
    file.open(fileName);

    std::string line;

    // Четем ред по ред
    while (std::getline(file, line))
    {
        // От всеки ред създаваме по един хотел
        std::vector<std::string> elements = split(line, ',');
        result.push_back(Hotel(
            elements[0],
            elements[1],
            elements[2],
            std::stod(elements[3]), // Помощна функция за конвертиране на string към double
            std::stod(elements[4]),
            std::stoi(elements[5]) // Помощна функция за конвертиране на string към int
            ));
    }

    // Грижим се за освобождаването на потока
    file.close();

    return result;
}
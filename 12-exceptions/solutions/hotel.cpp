#include "hotel.h"

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

std::vector<Hotel> readHotels(CSV csv)
{
    return csv.as<Hotel>([](Row row) -> Hotel { 
        if(row.cells.size() != 6)
        {
            throw std::runtime_error("Expected 6 columns, got " + std::to_string(row.cells.size()));
        }
        
        return Hotel(
            row.cells[0].value,
            row.cells[1].value,
            row.cells[2].value,
            std::stod(row.cells[3].value),
            std::stod(row.cells[4].value),
            std::stoi(row.cells[5].value)
        ); 
    });
}

CSV toCsv(std::vector<Hotel> hotels)
{
    std::vector<Header> headers;
    headers.push_back(Header("id", 0));
    headers.push_back(Header("name", 1));
    headers.push_back(Header("address", 2));
    headers.push_back(Header("x", 3));
    headers.push_back(Header("y", 4));
    headers.push_back(Header("rooms", 5));

    std::vector<Row> rows;
    int rowNumber = 1;
    for (Hotel h : hotels)
    {
        std::vector<Cell> cells;
        cells.push_back(Cell(headers[0], h.id));
        cells.push_back(Cell(headers[1], h.name));
        cells.push_back(Cell(headers[2], h.address));
        cells.push_back(Cell(headers[3], std::to_string(h.x)));
        cells.push_back(Cell(headers[4], std::to_string(h.y)));
        cells.push_back(Cell(headers[5], std::to_string(h.rooms)));

        rows.push_back(Row(rowNumber++, cells));
    }

    return CSV(headers, rows);
}
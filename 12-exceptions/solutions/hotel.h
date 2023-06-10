#include <string>
#include <vector>

#include "csv.h"

class Hotel
{
private:
    std::string id;
    std::string name;
    std::string address;
    double x;
    double y;
    int rooms;
public:
    Hotel();
    Hotel(const std::string&, const std::string&, const std::string&, double, double, int);
    bool operator==(const Hotel&) const;

    friend CSV toCsv(std::vector<Hotel>);
};

std::vector<Hotel> readHotels(CSV);

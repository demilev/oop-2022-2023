#include <string>
#include <vector>

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

    // friend функция за записване на вектор от хотели във файл.
    // Забележете, че този път подаваме името на файла като параметър.
    friend void write(const std::vector<Hotel>&, const std::string&);    
};

// Функция за четене на вектор от хотели от файл.
// Забележете, че този път подаваме името на файла като параметър.
std::vector<Hotel> read(const std::string&);

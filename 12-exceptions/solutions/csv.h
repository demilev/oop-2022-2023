#include <vector>
#include <string>

struct Header
{
    std::string name;
    int index;
};

struct Cell
{
    Header header;
    std::string value;
};

struct Row
{
    int rowNumber;
    std::vector<Cell> cells;
};

class CSV
{
private:
    std::vector<Header> headers;
    std::vector<Row> rows;
};

class CSVParser
{
public:
    CSV read(std::string file);
};
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <exception>

class InvalidRowException : public std::exception
{
private:
    int rowNumber;
    int expectedNumberOfElements;
    int actualNumberOfElements;
    std::string message;

public:
    InvalidRowException(
        int rowNumber,
        int expectedNumberOfElements,
        int actualNumberOfElements) : rowNumber(rowNumber), expectedNumberOfElements(expectedNumberOfElements), actualNumberOfElements(actualNumberOfElements)
    {
        message = ("Row " + std::to_string(rowNumber) +
                   " has " + std::to_string(actualNumberOfElements) +
                   " elements but " + std::to_string(expectedNumberOfElements) + " were expected");
    }

    const char *what()
    {
        return message.c_str();
    }
};

struct Header
{
    std::string name;
    int index;

    Header(std::string name, int index) : name(name), index(index) {}
};

struct Cell
{
    Header header;
    std::string value;

    Cell(Header header, std::string value) : header(header), value(value) {}
};

struct Row
{
    int rowNumber;
    std::vector<Cell> cells;

    Row(int rowNumber, std::vector<Cell> cells) : rowNumber(rowNumber), cells(cells) {}
};

class CSV
{
private:
    std::vector<Header> headers;
    std::vector<Row> rows;

public:
    CSV(std::vector<Header> headers, std::vector<Row> rows) : headers(headers), rows(rows) {}

    std::vector<Header> getHeaders() const
    {
        return headers;
    }

    std::vector<Row> getRows() const
    {
        return rows;
    }

    template <typename T>
    std::vector<T> as(std::function<T(Row)> convert)
    {
        std::vector<T> result;

        for (Row row : rows)
        {
            result.push_back(convert(row));
        }

        return result;
    }
};

class CSVParser
{
private:
    static std::vector<std::string> split(const std::string &s, char delimeter)
    {
        std::vector<std::string> result;
        std::string current;

        for (const char &c : s)
        {
            if (c != delimeter)
            {
                current.push_back(c);
            }
            else
            {
                result.push_back(current);
                current = "";
            }
        }

        result.push_back(current);

        return result;
    }

    static std::vector<Header> readHeaders(std::string line)
    {
        std::vector<Header> result;
        std::vector<std::string> elements = split(line, ',');
        for (int i = 0; i < elements.size(); i++)
        {
            result.push_back(Header(elements[i], i));
        }

        return result;
    }

    static Row readRow(int rowNumber, std::vector<Header> headers, std::string line)
    {
        std::vector<Cell> cells;
        std::vector<std::string> elements = split(line, ',');

        if (headers.size() != elements.size())
        {
            throw InvalidRowException(rowNumber, elements.size(), headers.size());
        }

        for (int i = 0; i < elements.size(); i++)
        {
            cells.push_back(Cell(headers[i], elements[i]));
        }
        return Row(rowNumber, cells);
    }

public:
    static CSV read(std::string fileName)
    {
        std::ifstream file;
        file.open(fileName);

        std::string line;
        std::getline(file, line);
        std::vector<Header> headers = readHeaders(line);

        std::vector<Row> rows;
        int rowIndex = 1;

        while (std::getline(file, line))
        {
            rows.push_back(readRow(rowIndex, headers, line));
        }

        file.close();

        return CSV(headers, rows);
    }
};

class CSVWriter
{
public:
    static void write(std::string fileName, const CSV &csv)
    {
        std::ofstream file;
        file.open(fileName);

        std::vector<Header> headers = csv.getHeaders();
        std::vector<Row> rows = csv.getRows();

        if (!headers.empty())
        {

            for (int i = 0; i < headers.size() - 1; i++)
            {
                file << headers[i].name << ",";
            }

            file << headers[headers.size() - 1].name << std::endl;

            for (Row r : rows)
            {
                if (!r.cells.empty())
                {
                    for (int j = 0; j < r.cells.size() - 1; j++)
                    {
                        file << r.cells[j].value << ",";
                    }

                    file << r.cells[r.cells.size() - 1].value << std::endl;
                }
            }
        }

        file.close();
    }
};

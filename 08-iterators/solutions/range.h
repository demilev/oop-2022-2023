#pragma once


class RangeIterator
{
private:
    int element;
public:
    RangeIterator(int);
    
    int operator*();
    RangeIterator &operator++();
    bool operator!=(const RangeIterator &other);
};

class Range
{
private:
    int from;
    int to;

public:
    Range(int, int);
    bool contains(int);
    int size();

    RangeIterator begin();
    RangeIterator end();
};

#include "range.h"


Range::Range(int from, int to): from(from), to(to) {}

bool Range::contains(int x)
{
    return x >= from && x <= to;
}

int Range::size()
{
    return (to - from) + 1;
}

RangeIterator Range::begin()
{
    return RangeIterator(from);
}

RangeIterator Range::end()
{
    return RangeIterator(to + 1);
}

RangeIterator::RangeIterator(int element): element(element) {}

int RangeIterator::operator*()
{
    return element;
}

RangeIterator& RangeIterator::operator++()
{
    element += 1;
    return *this;
}

bool RangeIterator::operator!=(const RangeIterator& other)
{
    return element != other.element;
}


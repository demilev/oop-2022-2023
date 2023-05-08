#include <iostream>

#include "range.h"
#include "../../lib/list.h"
#include "../../lib/vector.h"

int main()
{
    Range r(3, 10);

    for (int i : r)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    LinkedList<int> l;
    for (int i = 0; i < 1000000; i++)
    {
        l.pushFront(i);
    }

    // Много бавно:
    //
    // for (int i = 0; i < l.getSize(); i++)
    // {
    //     std::cout << l.get(i) << " ";
    // }

    // Оптимизиран вариант
    //
    // for (int i : l)
    // {
    //     std::cout << i << " ";
    // }
    //

    LinkedList<int> l1;
    l1.pushBack(2);
    l1.pushBack(3);
    l1.pushBack(5);

    for (int& i : l1)
    {
        i *= 2;
    }

    for (const int i : l1)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;


    Vector<int> v;
    v.add(4);
    v.add(9);
    v.add(-5);

    for (int& i : v)
    {
        i *= 2;
    }

    for (const int i : v)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    return 0;
}
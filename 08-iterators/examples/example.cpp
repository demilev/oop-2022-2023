#include "../../lib/list.h"
#include "../../lib/vector.h"

#include <iostream>

// template <typename Collection>
// void print(Collection c)
// {
//     for (int i = 0; i < c.getSize(); i++)
//     {
//         std::cout << c.get(i) << " ";
//     }

//     std::cout << std::endl;
// }

template <typename Collection, typename T>
void print(Collection c)
{
    for (T elem : c)
    {
        std::cout << elem << " ";
    }

    std::cout << std::endl;
}


// template <typename Collection>
// void print(Collection c)
// {
//     // for (int e : c)
//     // {
//     //   std::cout << e;     
//     //  }
//     //
//     for (Iterator i = c.begin(); i != c.end(); i++)
//     {
//         int e = *i;
//         std::cout << e << " ";
//     }

//     std::cout << std::endl;
// }


template <typename T>
class Iterator
{
    T operator*();
    Iterator& operator++();
    bool operator != (const Iterator &other); 
};

int main()
{

    LinkedList<int> l;
    l.pushBack(1);
    l.pushBack(2);
    l.pushBack(3);


    Vector<double> v;
    v.add(2.5);
    v.add(-3);

    // print(l);
    // print(v);

    return 0;
}
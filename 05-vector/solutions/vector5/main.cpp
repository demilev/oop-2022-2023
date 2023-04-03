#include <iostream>
#include "polynomial.h"
#include "todo.h"

int main()
{
    Polynomial p1;
    p1.addCoef(3);
    p1.addCoef(2.5);
    p1.addCoef(13);
    p1.addCoef(-2);
    p1.addCoef(-5);

    p1.print();
    p1.removeCoef();
    p1.print();

    std::cout << p1(1) << std::endl;

    TODOList list;
    list.addTask(Task("homework", 3));
    list.addTask(Task("cleaning", 1));
    list.addTask(Task("fitness", 2));

    list.print();

    TODOList other(list);

    list.removeTask(Task("homework", 0));

    list.print();
    other.print();

    return 0;
}
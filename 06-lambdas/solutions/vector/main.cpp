#include <iostream>

#include "task.h"
#include "vector.h"

// Помощна функция за отпечатване на елементите на вектор
template <typename T>
void printVector(const Vector<T> &v)
{
    for (int i = 0; i < v.getSize(); i++)
    {
        std::cout << v.get(i) << " ";
    }

    std::cout << std::endl;
}

int main()
{
    // Вектор с числа
    Vector<int> v;
    v.add(1);
    v.add(2);
    v.add(12);
    v.add(35);

    // Вектор със задачи
    Vector<Task> tasks;
    tasks.add(Task("task1", 60));
    tasks.add(Task("task2", 50));
    tasks.add(Task("task2", 20));

    // Примери за използване на `find` с произволни ламбда изрази
    std::cout << v.find([](int x) -> bool { return x % 2 == 0; }) << std::endl;
    std::cout << v.find([](int x) -> bool { return x > 0; }) << std::endl;
    std::cout << v.find([](int x) -> bool { return x % 3 == 1; }) << std::endl;
    std::cout << tasks.find([](Task t) -> bool { return t.getDuration() < 45; }) << std::endl;

    // Примери за използване на `find` с произволни ламбда изрази
    std::cout << v.exists([](int x) -> bool { return x == 12; }) << std::endl;
    std::cout << tasks.exists([](Task t) -> bool { return t.getDuration() == 20; }) << std::endl;

    // Използване на map, за да получим вектор с квадратите на оригиналните числа
    Vector<int> squared = v.map<int>([](int x) -> int { return x * x; });
    printVector(squared);

    // Използване на map, за да получим вектор с продължителността на задачите
    Vector<int> durations = tasks.map<int>([](Task x) -> int { return x.getDuration(); });
    printVector(durations);

    // Използваме foldLeft, за да намерим общата продължителност на задачите
    int totalDuration = tasks.foldLeft<int>(0, [](int duration, Task x) -> int { return duration + x.getDuration(); });
    std::cout << "Total task duration: " << totalDuration << std::endl;

    // Пример за използване на foldRight за обръщане на Vector. 
    // Започваме с празен вектор и на всяка стъпка му добавяме текущия елемент
    Vector<int> reversed = v.foldRight<Vector<int>>(Vector<int>(), [](Vector<int> result, int x) -> Vector<int> { 
        result.add(x);
        return result; 
    });
    printVector(reversed);

    // Алтернативен подход за обръщане на Vector.
    // Отново започваме с празен вектор, но този път ще се възползваме от факта, че ламбда функцията може да достъпва неща от външния контекст.
    // Забележете, че подаваме reversed2 по референция в capture list-а на ламбда функцията.
    Vector<int> reversed2;
    v.foldRight<int>(0, [&reversed2](int count, int x) -> int { 
        reversed2.add(x);
        return count + 1; 
    });
    printVector(reversed2);

    // От всяко число на оригиналния Vector, образуваме поредицата от числата от 1 до abs(x)
    Vector<int> longList = v.flatMap<int>([](int x) -> Vector<int> {
        Vector<int> result(abs(x));
        for (int i = 1; i <= abs(x); i++)
        {
            result.add(i);
        }

        return result;
    });
    printVector(longList);

    return 0;
}
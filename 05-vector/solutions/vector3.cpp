#include <iostream>

/*
    Версията на класа от предната задача, но с малко повече функционалност.
*/
class Vector
{
private:
    int size;
    int capacity;
    double *arr;

    void cleanup()
    {
        delete[] arr;
    }

    void copy(const Vector &other)
    {
        size = other.size;
        capacity = other.capacity;
        arr = new double[capacity];
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    void resize()
    {
        double *newArr = new double[capacity * 2];
        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }

        arr = newArr;
        capacity *= 2;
    }

public:
    Vector() : Vector(8) {}

    Vector(int capacity) : size(0), capacity(capacity), arr(new double[capacity]) {}

    Vector(const Vector &other)
    {
        copy(other);
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            cleanup();
            copy(other);
        }

        return *this;
    }

    ~Vector()
    {
        cleanup();
    }

    int getSize() const
    {
        return size;
    }

    double get(int index)
    {
        return arr[index];
    }

    void add(double elem)
    {
        if (size >= capacity)
        {
            resize();
        }

        arr[size++] = elem;
    }

    void remove()
    {
        size--;
    }

    // Метод за търсене на индекса на елемент в масива
    int find(const double &x)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == x)
            {
                return i;
            }
        }

        return -1;
    }

    // Метод за добавяне на елемент на произволна позиция.
    // Проверките за коректност са пропуснати
    void addAtIndex(double elem, int index)
    {
        // Ако сме достигнали максималния капацитет, преоразмеряваме
        if (size >= capacity)
        {
            resize();
        }

        // Изместваме всичко след index с една позиция надясно
        for (int i = size; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }

        // Добавяме новия елемент на index
        arr[index] = elem;

        // Увеличаваме реалния размер
        size++;
    }

    void removeAtIndex(int index)
    {
        // Изместваме всичко след index с една позиция наляво
        for (int i = index; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        // Намаляме реалния размер
        size--;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    // Метод, който връща обърната версия на текущия масив
    Vector reverse()
    {
        // Още от началото знаем с какъв капацитет трябва да е резултатът.
        Vector result(capacity);

        // Обхождаме елементите на текущия масив отзад напред и ги добавяме към резултата
        for (int i = size - 1; i >= 0; i--)
        {
            // Вече имам метод за добавяне на елемент, така че си го ползвам. Няма нужда да откривам топлата вода
            result.add(arr[i]);
        }

        return result;
    }

    // Метод, който връща версия на текущия масив само с елементите, които отговарят на булево условие
    Vector filter(bool (*p)(double))
    {
        Vector result(capacity);

        for (int i = 0; i < size; i++)
        {
            if (p(arr[i]))
            {
                result.add(arr[i]);
            }
        }

        return result;
    }
};
#include <iostream>

/*
    Финалната версия на класа е шаблонна. Позволява да създаваме масиви от произволни елементи.
    В имплементацията просто сме сменили всяко срещане на double с Т
*/

template <typename T>
class Vector
{
private:
    int size;
    int capacity;
    T *arr;

    void cleanup()
    {
        delete[] arr;
    }

    void copy(const Vector &other)
    {
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    void resize()
    {
        T *newArr = new T[capacity * 2];
        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }

        arr = newArr;
        capacity *= 2;
    }

public:
    Vector() : Vector(8) {}

    Vector(int capacity) : size(0), capacity(capacity), arr(new T[capacity]) {}

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

    T get(int index)
    {
        return arr[index];
    }

    void add(T elem)
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

    int find(const T &x)
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

    void addAtIndex(const T &elem, int index)
    {
        if (size >= capacity)
        {
            resize();
        }

        for (int i = size; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }

        arr[index] = elem;

        size++;
    }

    void removeAtIndex(int index)
    {
        for (int i = index; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        size--;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    Vector reverse()
    {
        Vector result(capacity);

        for (int i = size - 1; i >= 0; i--)
        {
            result.add(arr[i]);
        }

        return result;
    }

    Vector filter(bool (*p)(T))
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

bool isPositive(double d)
{
    return d >= 0;
}

int main()
{
    // Примерно използване на класа
    Vector<double> v;
    v.add(1);
    v.add(2);
    v.add(-42);
    v.add(-5);
    v.remove();

    for (int i = 0; i < v.getSize(); i++)
    {
        std::cout << v.get(i) << " ";
    }

    std::cout << std::endl;

    std::cout << v.find(2) << std::endl;
    std::cout << v.find(-5) << std::endl;

    Vector<double> reversed = v.reverse();
    for (int i = 0; i < reversed.getSize(); i++)
    {
        std::cout << reversed.get(i) << " ";
    }

    std::cout << std::endl;

    Vector<double> positives = v.filter(isPositive);
    for (int i = 0; i < positives.getSize(); i++)
    {
        std::cout << positives.get(i) << " ";
    }

    std::cout << std::endl;

    return 0;
}
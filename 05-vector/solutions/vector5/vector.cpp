#include "vector.h"

template <typename T>
void Vector<T>::cleanup()
{
    delete[] arr;
}

template <typename T>
void Vector<T>::copy(const Vector<T> &other)
{
    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
void Vector<T>::resize()
{
    T *newArr = new T[capacity * 2];
    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }

    arr = newArr;
    capacity *= 2;
}

template <typename T>
Vector<T>::Vector() : Vector(8) {}

template <typename T>
Vector<T>::Vector(int capacity) : size(0), capacity(capacity), arr(new T[capacity]) {}

template <typename T>
Vector<T>::Vector(const Vector &other)
{
    copy(other);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (this != &other)
    {
        cleanup();
        copy(other);
    }

    return *this;
}

template <typename T>
Vector<T>::~Vector()
{
    cleanup();
}

template <typename T>
int Vector<T>::getSize() const
{
    return size;
}

template <typename T>
T Vector<T>::get(int index) const
{
    return arr[index];
}

template <typename T>
void Vector<T>::add(T elem)
{
    if (size >= capacity)
    {
        resize();
    }

    arr[size++] = elem;
}

template <typename T>
void Vector<T>::remove()
{
    size--;
}

template <typename T>
int Vector<T>::find(const T &x)
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

template <typename T>
void Vector<T>::addAtIndex(const T &elem, int index)
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

template <typename T>
void Vector<T>::removeAtIndex(int index)
{
    for (int i = index; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    size--;
}

template <typename T>
bool Vector<T>::isEmpty()
{
    return size == 0;
}

template <typename T>
Vector<T> Vector<T>::reverse()
{
    Vector result(capacity);

    for (int i = size - 1; i >= 0; i--)
    {
        result.add(arr[i]);
    }

    return result;
}

template <typename T>
Vector<T> Vector<T>::filter(bool (*p)(T))
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

#pragma once

#include <functional>

template <typename T, typename ReturnT>
class VectorIndexIterator;

template <typename T, typename ReturnT>
class VectorPtrIterator;

template <typename T>
class Vector
{
private:
    int size;
    int capacity;
    T *arr;

    void cleanup();
    void copy(const Vector &);
    void resize();

public:
    Vector();
    Vector(int);
    Vector(const Vector &);

    Vector &operator=(const Vector &);

    ~Vector();

    int getSize() const;

    T get(int) const;
    T& get(int);

    void add(T);

    void remove();

    int find(const T &);

    void addAtIndex(const T &, int);

    void removeAtIndex(int);

    bool isEmpty();

    Vector reverse();

    Vector filter(bool (*)(T));

    // Новите методи:
    int find(std::function<bool(T)>);

    bool exists(std::function<bool(T)>);

    template <typename U>
    Vector<U> map(std::function<U(T)>);

    template <typename U>
    U foldLeft(U, std::function<U(U, T)>);

    template <typename U>
    U foldRight(U, std::function<U(U, T)>);

    template <typename U>
    Vector<U> flatMap(std::function<Vector<U>(T)>);

    VectorPtrIterator<T, T> begin() const;
    VectorPtrIterator<T, T> end() const;

    VectorPtrIterator<T, T &> begin();
    VectorPtrIterator<T, T &> end();
};

template <typename T, typename ReturnT>
class VectorIndexIterator
{
private:
    int index;
    Vector<T> *v;

public:
    VectorIndexIterator(int, Vector<T> *);

    ReturnT operator*();
    VectorIndexIterator<T, ReturnT> &operator++();
    bool operator!=(const VectorIndexIterator<T, ReturnT> &);
};

template <typename T, typename ReturnT>
class VectorPtrIterator
{
private:
    T *elem;

public:
    VectorPtrIterator(T *);

    ReturnT operator*();
    VectorPtrIterator<T, ReturnT> &operator++();
    bool operator!=(const VectorPtrIterator<T, ReturnT> &);
};

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
T& Vector<T>::get(int index)
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

template <typename T>
int Vector<T>::find(std::function<bool(T)> p)
{
    for (int i = 0; i < size; i++)
    {
        if (p(arr[i]))
        {
            return i;
        }
    }

    return -1;
}

template <typename T>
bool Vector<T>::exists(std::function<bool(T)> p)
{
    return find(p) > 0;
}

template <typename T>
template <typename U>
Vector<U> Vector<T>::map(std::function<U(T)> f)
{
    Vector<U> result(this->capacity);

    for (int i = 0; i < this->size; i++)
    {
        result.add(f(arr[i]));
    }

    return result;
}

template <typename T>
template <typename U>
U Vector<T>::foldLeft(U acc, std::function<U(U, T)> op)
{
    for (int i = 0; i < this->size; i++)
    {
        acc = op(acc, arr[i]);
    }

    return acc;
}

template <typename T>
template <typename U>
U Vector<T>::foldRight(U acc, std::function<U(U, T)> op)
{
    for (int i = this->size - 1; i >= 0; i--)
    {
        acc = op(acc, arr[i]);
    }

    return acc;
}

template <typename T>
template <typename U>
Vector<U> Vector<T>::flatMap(std::function<Vector<U>(T)> f)
{
    Vector<U> result(this->capacity);

    for (int i = 0; i < this->size; i++)
    {
        Vector<U> current = f(arr[i]);
        for (int j = 0; j < current.getSize(); j++)
        {
            result.add(current.get(j));
        }
    }

    return result;
}

template <typename T>
VectorPtrIterator<T, T &> Vector<T>::begin()
{
    return VectorPtrIterator<T, T &>(arr);
}

template <typename T>
VectorPtrIterator<T, T &> Vector<T>::end()
{
    return VectorPtrIterator<T, T &>(arr + size);
}

template <typename T>
VectorPtrIterator<T, T> Vector<T>::begin() const
{
    return VectorPtrIterator<T, T>(arr);
}

template <typename T>
VectorPtrIterator<T, T> Vector<T>::end() const
{
    return VectorPtrIterator<T, T>(arr + size);
}

template <typename T, typename ReturnT>
VectorIndexIterator<T, ReturnT>::VectorIndexIterator(int index, Vector<T> *v) : index(index), v(v) {}

template <typename T, typename ReturnT>
ReturnT VectorIndexIterator<T, ReturnT>::operator*()
{
    return v->get(index);
}

template <typename T, typename ReturnT>
VectorIndexIterator<T, ReturnT> &VectorIndexIterator<T, ReturnT>::operator++()
{
    index++;
    return *this;
}

template <typename T, typename ReturnT>
bool VectorIndexIterator<T, ReturnT>::operator!=(const VectorIndexIterator<T, ReturnT> &other)
{
    return this->index != other.index || this->v != other.v;
}

template <typename T, typename ReturnT>
VectorPtrIterator<T, ReturnT>::VectorPtrIterator(T *elem) : elem(elem) {}

template <typename T, typename ReturnT>
ReturnT VectorPtrIterator<T, ReturnT>::operator*()
{
    return *elem;
}

template <typename T, typename ReturnT>
VectorPtrIterator<T, ReturnT> &VectorPtrIterator<T, ReturnT>::operator++()
{
    elem++;
    return *this;
}

template <typename T, typename ReturnT>
bool VectorPtrIterator<T, ReturnT>::operator!=(const VectorPtrIterator<T, ReturnT> &other)
{
    return this->elem != other.elem;
}
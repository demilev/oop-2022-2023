#pragma once

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

    void add(T);

    void remove();

    int find(const T &);

    void addAtIndex(const T &, int);

    void removeAtIndex(int);

    bool isEmpty();

    Vector reverse();

    Vector filter(bool (*)(T));
};

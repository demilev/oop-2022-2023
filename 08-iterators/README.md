# Тема 8, Итератори, 25.04.2023

## Итератор

```c++
template <typename T>
class Iterator
{
    T operator*();
    Iterator& operator++();
    bool operator != (const Iterator &other); 
};
```

## for цикъл върху колекция

```c++
LinkedList<int> list;
for (int i : list)
{
    std::cout << i << " ";
}
```

грубо казано се превежда до

```c++
LinkedList<int> list;
for (Iterator it = list.begin(); it != list.end(); it++)
{
    int i = *it;
    std::cout << i << " "; 
}
```

### Пълен минимален пример

```c++
template <typename T>
class Collection
{
public:
    Iterator<T> begin();
    Iterator<T> end();
};

template <typename T>
class Iterator
{
    T operator*();
    Iterator& operator++();
    bool operator != (const Iterator &other); 
};

int main()
{
    Collection<int> c;

    for (int i : c)
    {
        std::cout << i << " ";    
    }
}
```

## Задачи

### Зад. 1 - [Решение](./solutions/range.cpp)

Имплементирайте клас `Range`, който предсатвлява краен интервал от цели числа. Добавете

* конструктор `Range(int, int)`, който задава долна и горна граница на интервала
* метод `bool contains(int)`, който проверява дали дадено число принадлежи на интервала
* метод `int size()`, който връща броя на числата в този интервал

Имплементирайте и клас `RangeIterator`, с който ще можем да обхождаме интервала. За целта добавете:

* методи `RangeIterator begin()` и `RangeIterator end()` в класа `Range`
* `int operator*()` оператор в класа `RangeIterator`
* `RangeIterator& operator++()` оператор в класа `RangeIterator`
* `bool operator != (const RangeIterator &other)` оператор в класа `RangeIterator`

### Зад. 2 - [Решение](../lib/list.h) (Разгледайте `begin` и `end` методите на класа `LinkedList` и класа `LinkedListIterator`)

Добавете итератор за класа `LinkedList`.

### Зад. 3 - [Решение](../lib/list.h) (Разгледайте `begin` и `end` методите на класа `LinkedList` и класа `LinkedListIterator`)

Добавете итератор за класа `LinkedList`, който да позволява промяна на елементите на списъка.

### Зад. 4 - [Решение](../lib/vector.h) (Разгледайте `begin` и `end` методите на класа `Vector` и класовете `VectorIndexIterator` и `VectorPtrIterator`)

Добавете итератор за класа `Vector`. Направете имплементация, която:

* работи с индеските на масива
* работи само с указатели към елементите на масива

Какви са разликите между двете?
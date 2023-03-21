# Тема 3, Класове, 14.03.2023

## struct vs class

```c++

struct NumberStruct
{
    int x;
};

class NumberClass 
{
public:
    int x;
};
```

## Методи

```c++
class Number 
{
public:
    int x;
    void print()
    {
        std::cout << x;
    }
};
```

## Конструктори

```c++
class Number 
{
public:
    int x;
    Number()
    {
        x = 5;
    }
    Number(int n)
    {
        x = n;
    }
};
```

## Указатели към обекти

```c++
Number n(3);
Number *ptr = &n;
(*ptr).print();
ptr->print();
```

## Оператори

```c++
class Number
{
public:
    int x;
    Number(int n) {
        x = n;
    }

    Number operator+(Number other) {
        return Number(x + other.x);
    }
};
```

## Задачи

### Зад. 1 - [Решение](./solutions/point.cpp)

Напишете клас, който описва точка в равнината. Добавете

* конструктор по подразбиране
* конструктор с две реални числа
* метод, който отпечатва точката на екрана
* метод, който намира разстоянието между текущата точка и друга такава
* оператор за събиране на две точки
* оператор за умножаване на точка с число
* оператор за сравняване на две точки за равенство
* функция, която казва дали дадена точка се намира в масив от точки

### Зад. 2 - [Решение](./solutions/triangle.cpp)

Напишете клас, който описва триъгълник в равнината. Добавете

* конструктор по подразбиране
* конструктор с три точки(върховете на триъгълника)
* конструктор с координати на върховете
* метод, който връща периметъра на триъгълника
* метод, който връща лицето на триъгълника
* оператор за сравняване на лицатата на два триъгълника
* функция, която по подаден масив с триъгълници, връща триъгълника с най-голямо лице
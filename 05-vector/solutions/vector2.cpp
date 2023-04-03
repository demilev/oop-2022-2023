/*
    Оптимизиран вариант на класа Vector, при който преоразмеряваме само при нужда.
    Забележете, че нищо в публичните методи не се променя като сигнатура.
    Интерфейсът остава същия, променя се имплементацията. Това е силата на добрата абстракция.
*/

class Vector
{
private:
    int size;
    int capacity; // Допълнителна член данна, която показва текущия максимален капацитет
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

    // Помощен метод, който ще позлваме, когато трябва да заделим нова памет.
    // Идеята е да заделим двойно по-голям буфер и да преместим елементите там.
    void resize()
    {
        // Заделяме двойно повече нова памет
        double *newArr = new double[capacity * 2];
        for (int i = 0; i < size; i++)
        {
            // Копираме всички стари елементи
            newArr[i] = arr[i];
        }

        // Обновяваме член данните
        arr = newArr;
        capacity *= 2;
    }

public:
    // Делегиране на конструктори. Конструктура по подразбиране "извиква" конструктура с един параметър
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
        // Ако сме достигнали максималния капацитет, преоразмеряваме
        if (size >= capacity)
        {
            resize();
        }

        // Добавяме новия елемент накрая и увеличаваме реалния размер на масива.
        // Можем да достъпим arr[size], защото знаем, че сме заделили повече памет.
        arr[size++] = elem;
    }

    void remove()
    {
        // "Махаме" последния елемент. Помислете за вариант, в който преоразмеряваме масива и при тази операция
        size--;
    }
};

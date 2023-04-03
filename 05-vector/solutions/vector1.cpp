
/*
    Базов вариант на класа Vector, който поддържа масив от реални числа и при който
    преоразмеряваме при всяко добяване/премахване на елемент.
*/
class Vector
{
    // Енкаспулираме член данните и вътрешните методи, като ги правим private.
    // Така те ще бъдат достъпни само в тялото на класа
private:
    int size;
    double *arr;

    // Познатите функции cleanup и copy
    void cleanup()
    {
        delete[] arr;
    }

    void copy(const Vector &other)
    {
        size = other.size;
        arr = new double[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }

public:
    // Конструктор с инициализиращ списък
    Vector() : size(0), arr(nullptr) {}

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
        // Заделяме нова памет
        double *newArr = new double[size + 1];
        for (int i = 0; i < size; i++)
        {
            // Копираме всички стари елементи
            newArr[i] = arr[i];
        }

        // Добавяме новия накрая
        newArr[size] = elem;

        // Зачистваме текущо използваната памет
        cleanup();

        // Обновяваме член данните
        arr = newArr;
        size++;
    }

    void remove()
    {
        // Заделяме нова памет
        double *newArr = new double[size - 1];
        for (int i = 0; i < size - 1; i++)
        {
            // Копираме всички стари елементи без послендия
            newArr[i] = arr[i];
        }

        // Зачистваме текущо използваната памет
        cleanup();

        // Обновяваме член данните
        arr = newArr;
        size--;
    }
};
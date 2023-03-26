#include <iostream>

/*
    Да се имплементира клас `Polynomial`, представляващ полином от произволна степен. Добавете:
        * конструктор по подразбиране, копи конструктор, оператор равно и деструктор
        * метод за отпечатване на полинома на стандартния изход
        * operator() - по подадено число пресмята полинома
        * метод за добавяне и премахване на коефициент
        * оператор за събиране на два полинома
*/

/* Забележка! В имплементацията са пропуснати проверките за коректност. Помислете къде трябва да бъдат добавени. */
class Polynomial
{
public:
    // Един полином се определея еднозначно от коефициентите си, затова те ще са нашите член данни
    int power;
    double *coef;

    // Функция, която ще ползваме, когато трябва да освободим паметта използвана от текущия полином
    void cleanup()
    {
        delete[] coef;
    }

    // Функция за копиране данните на друг полином в текущия
    void copy(const Polynomial &other)
    {
        // Заделяме памет за текущия масив от коефициенти
        coef = new double[other.power + 1];
        power = other.power;
        for (int i = 0; i <= power; i++)
        {
            // Копираме всеки елемент от другия полином в текущия
            coef[i] = other.coef[i];
        }
    }

    // Конструктор по подразбиране
    Polynomial()
    {
        power = -1;
        coef = nullptr;
    }

    // Конструктор с масив от елементи
    Polynomial(double coef[], int size)
    {
        // Заделяме точно толкова памет, колкото ще ни трябва
        this->coef = new double[size];
        power = size - 1;
        for (int i = 0; i < size; i++)
        {
            this->coef[i] = coef[i];
        }
    }

    // Деструктор за класа. Освобождаваме динамичната памет
    ~Polynomial()
    {
        cleanup();
    }

    // Копи конструктор
    Polynomial(const Polynomial &other)
    {
        copy(other);
    }

    // Оператор равно
    Polynomial &operator=(const Polynomial &other)
    {
        // Правим, каквото и да е, само ако другият обект е различен от текущия
        if (this != &other)
        {
            // Почистваме текущата памет, защото оператор равно се ползва върху вече създадени обекти
            cleanup();
            // Копираме other в this
            copy(other);
        }

        return *this;
    }

    // Метод, който изчислява стойността на полинома в дадена точка - това е главното, което искаме да правим с полиномите
    double calculate(double x)
    {
        double result = 0;
        double currentPower = 1;
        for (int i = 0; i <= power; i++)
        {
            result += coef[i] * currentPower;
            currentPower *= x;
        }

        return result;
    }

    // Един интересен оператор, който ще ни позволи да извикаваме нашите полиноми подобно на c++ функции, въпреки че не са.
    // Правим го, защото все пак полиномът е математическа функция
    double operator()(double x)
    {
        return calculate(x);
    }

    // Метод за отпечатване на текущото състояние на полинома
    void print()
    {
        for (int i = 0; i <= power; i++)
        {
            std::cout << coef[i] << " ";
        }

        std::cout << std::endl;
    }

    // Метод за добавяне на нов коефициент
    void addCoef(double c)
    {
        // Заделяме нова памет
        double *newCoef = new double[power + 1 + 1];
        for (int i = 0; i <= power; i++)
        {
            // Копираме всички стари елементи
            newCoef[i] = coef[i];
        }

        // Добавяме новия накрая
        newCoef[power + 1] = c;

        // Зачистваме текущо използваната памет
        cleanup();

        // Обновяваме член данните
        coef = newCoef;
        power++;
    }

    // Метод за премахане на коефициент
    void removeCoef()
    {
        // Заделяме нова памет
        double *newCoef = new double[power];
        for (int i = 0; i < power; i++)
        {
            // Копираме всичко без последния елемент
            newCoef[i] = coef[i];
        }

        // Зачистваме текущо използваната памет
        cleanup();

        // Обновяваме член данните
        coef = newCoef;
        power--;
    }

    // Предефинираме оператор +, за да можем да събираме два полинома
    Polynomial operator+(const Polynomial &other)
    {
        int maxPower = std::max(power, other.power);
        int minPower = std::min(power, other.power);
        Polynomial result; // Създаваме полином, в който ще трупаме резултата

        // Добавяме сумата на коефициентите, докато стигнем по-малката от двете степени
        for (int i = 0; i <= minPower; i++)
        {
            result.addCoef(other.coef[i] + coef[i]);
        }

        // Добавяме останалите коефициенти на полинома от по-голяма степен
        if (other.power < power)
        {
            for (int i = minPower + 1; i <= maxPower; i++)
            {
                result.addCoef(coef[i]);
            }
        }
        else
        {
            for (int i = minPower + 1; i <= maxPower; i++)
            {
                result.addCoef(other.coef[i]);
            }
        }

        return result;
    }
};

int main()
{
    // Примери за използване на нашия клас за полином
    double arr[] = {1, 2, 3};
    Polynomial p(arr, 3);
    p.print();

    Polynomial p1;
    p1.addCoef(3);
    p1.addCoef(2.5);
    p1.addCoef(13);
    p1.addCoef(-2);
    p1.addCoef(-5);

    p1.print();
    p1.removeCoef();
    p1.print();

    std::cout << p1(1) << std::endl; // p1.operator()(1)

    (p + p1).print();

    return 0;
}
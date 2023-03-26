#include <iostream>

/*
    Да се имплементира клас `Task`, представляващ една задача за изпълнение. Всяка задача се характеризира с име с произволна дължина и време(в часове) за изпълнение. Добавете:
        * конструктор по подразбиране, копи конструктор, оператор равно и деструктор
        * метод за отпечатване на задачата на стандартния изход
        * оператор за сравнение на две задачи по име

    Имплементирайте и клас, описващ списък от задачи. Добавете:
        * конструктор по подразбиране, копи конструктор, оператор равно и деструктор
        * метод за отпечатване на всички задачи в списъка
        * метод за добавяне на задача
        * метод за премахване на задача
*/

class Task
{
public:
    // Както и условието подсказва, всяка задача си има име и продължителност
    char *name;
    int duration;

    // Познатият помощен метод за освобождаване на паметта. Тъй като името на задачата може да е с произволна дължина,
    // ще работим с динамична памет и ще трябва да се грижим за нея.
    void cleanup()
    {
        delete[] name;
    }

    // Познатият метод за копиране на друг обект в текущия
    void copy(const Task &other)
    {
        duration = other.duration;
        name = new char[strlen(other.name) + 1]; // Не забравяме да заделим памет за терминиращата нула
        strcpy(name, other.name);
    }

    // Стандартно изглеждащата голяма четворка
    Task()
    {
        name = nullptr;
        duration = 0;
    }

    Task(const Task &other)
    {
        copy(other);
    }

    ~Task()
    {
        cleanup();
    }

    Task &operator=(const Task &other)
    {
        if (this != &other)
        {
            cleanup();
            copy(other);
        }

        return *this;
    }

    // Добавяме все пак и още един конструктор за удобство
    Task(const char *name, int duration)
    {
        this->duration = duration;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void print()
    {
        std::cout << "Task: " << name << std::endl;
        std::cout << "Duration in hours: " << duration << std::endl;
    }

    // Оператор за сравнение на две задачи по име. Ползваме вградената функция за сравняване на низове
    bool operator==(const Task &other)
    {
        return strcmp(name, other.name) == 0;
    }
};

class TODOList
{
public:
    // Както и подсказва името на класа, той представя списък от задачи
    Task *tasks;
    int numberOfTasks;

    // Отново работим с динамична памет и съответно трябва да се погрижим за нея
    void cleanup()
    {
        delete[] tasks;
    }

    void copy(const TODOList &other)
    {
        numberOfTasks = other.numberOfTasks;
        tasks = new Task[numberOfTasks];
        for (int i = 0; i < numberOfTasks; i++)
        {
            tasks[i] = other.tasks[i]; // Тук ще се извика нашия предефиниран оператор = за класа Task
        }
    }

    // Добре познатата голяма четворка
    TODOList()
    {
        tasks = nullptr;
        numberOfTasks = 0;
    }

    TODOList(const TODOList &other)
    {
        copy(other);
    }

    ~TODOList()
    {
        cleanup();
    }

    TODOList &operator=(const TODOList &other)
    {
        if (this != &other)
        {
            cleanup();
            copy(other);
        }

        return *this;
    }

    void print()
    {
        std::cout << "The list has " << numberOfTasks << " tasks" << std::endl;
        for (int i = 0; i < numberOfTasks; i++)
        {
            std::cout << "Task " << i << ":" << std::endl;
            tasks[i].print();
        }
    }

    // Аналогична имплементация на метода за добавяне на коефициент към полином от предната задача.
    // Какво ви говори това?
    void addTask(const Task &task)
    {
        // Заделяме нова памет
        Task *newTasks = new Task[numberOfTasks + 1];
        for (int i = 0; i < numberOfTasks; i++)
        {
            // Копираме всички стари елементи
            newTasks[i] = tasks[i];
        }

        // Добавяме новия накрая
        newTasks[numberOfTasks] = task;

        // Зачистваме текущо използваната памет
        cleanup();

        // Обновяваме член данните
        tasks = newTasks;
        numberOfTasks++;
    }

    // Метод за премахване на елемент от списъка със задачи
    void removeTask(const Task &task)
    {

        // Намираме индекса, на който стои търсената задача
        int taskIndex = -1;
        for (int i = 0; i < numberOfTasks; i++)
        {
            if (tasks[i] == task) // Тук ще се извика нашия предефиниран оператор == за класа Task
            {
                taskIndex = i;
                break;
            }
        }

        // Ще трием нещо само ако търсената задача се среща в списъка от задачи
        if (taskIndex >= 0)
        {
            // Заделяме нова памет
            Task *newTasks = new Task[numberOfTasks - 1];
            int index = 0;
            for (int i = 0; i < taskIndex; i++)
            {
                // Копираме всички стари елементи до индекса
                newTasks[index++] = tasks[i];
            }

            for (int i = taskIndex + 1; i < numberOfTasks; i++)
            {
                // Копираме всички стари елементи след индекса
                newTasks[index++] = tasks[i];
            }

            // Зачистваме текущо използваната памет
            cleanup();

            // Обновяваме член данните
            tasks = newTasks;
            numberOfTasks--;
        }
    }
};

int main()
{
    // Примери за използване на нашите класове
    TODOList list;
    list.addTask(Task("homework", 3));
    list.addTask(Task("cleaning", 1));
    list.addTask(Task("fitness", 2));

    list.print();

    TODOList other(list);

    list.removeTask(Task("homework", 0));

    list.print();
    other.print(); // other трябва да е непроменен дори след като сме махнали елемент от list

    return 0;
}
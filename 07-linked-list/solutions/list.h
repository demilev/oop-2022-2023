#pragma once

#include <functional>

// Шаблонен клас за кутийка, която съдържа данни от шаблония тип и указател към следваща кутийка
template <typename T>
class Node
{
public:
    T data;
    Node *next;

    // Няколко конструктора
    Node();
    Node(const T &);
    Node(const T &, Node *);
};

// Свързаният списък ще представим като поредица от кутийки
template <typename T>
class LinkedList
{
private:
    // Пазим само информация за първата кутийка, защото всички други можем да ги стигнем през нея
    Node<T> *start;
    // Помощна променлива, в която ще държим актуалния размер на списъка, за да няма нужда да го преизчисляваме постоянно
    int size;

    // Стандартните ни функции за опериране с динамична памет
    void cleanup();
    void copy(const LinkedList<T> &);

public:
    //  Голяма четворка и един помощен конструктор 
    LinkedList();
    LinkedList(Node<T> *, int);
    LinkedList(const LinkedList<T> &);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &);

    // Методи за добавяне и премахване на елемент в началото
    void pushFront(const T &);
    void popFront();

    // Методи за достъпване на елемент в началото/края/произволен индекс
    T head();
    T last();
    T get(int);

    // Методи за добавяне и премахване на елемент в края
    void pushBack(const T &);
    void popBack();

    // Методи за добавяне и премахване на елемент на произволна позиция
    void insertAt(const T &, int);
    void removeAt(int);

    // Метод за обръщане на списъка
    LinkedList<T> reverse();

    // map операция
    template <typename U>
    LinkedList<U> map(std::function<U(T)>);

    // friend функция за обединяване на два сортирани списъка
    template <typename U>
    friend LinkedList<U> mergeLists(const LinkedList<U> &, const LinkedList<U> &);
};

template <typename T>
Node<T>::Node() : data(), next(nullptr) {}

// Делегираме изпълененито към конструктора с два параметъра
template <typename T>
Node<T>::Node(const T &data) : Node(data, nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node *next) : data(data), next(next) {}

// Делегираме изпълененито към конструктора с два параметъра
template <typename T>
LinkedList<T>::LinkedList() : LinkedList<T>(nullptr, 0) {}

template <typename T>
LinkedList<T>::LinkedList(Node<T> *start, int size) : start(start), size(size) {}

// Метод за почистване на паметта използвана от един списък
template <typename T>
void LinkedList<T>::cleanup()
{
    // Ако списъкът е празен, няма какво да зачистваме
    if (start == nullptr)
        return;

    // Ще пазим два указателя - един към текущата, кутия, която ще зачистваме 
    // и един към следващата, за да не губим връзката и да можем да продължим обхождането
    Node<T> *current = start;
    Node<T> *child = current->next;

    // Докато не стигнем края
    while (current != nullptr)
    {
        // Изтриваме текущата
        delete current;

        // Преминаваме към следващата
        current = child;
        if (child != nullptr)
            child = child->next;
    }
}

// Метод за копиране на един списък в текущия
template <typename T>
void LinkedList<T>::copy(const LinkedList<T> &other)
{
    // Ако другият е празен, няма какво да копираме
    if (other.start == nullptr)
    {
        this->start = nullptr;
        return;
    }

    // Създаваме началната кутия
    Node<T> *newStart = new Node<T>(other.start->data);
    this->start = newStart;

    // Ще пазим два указателя - един, който върви по другия списък и един, който върви по текущия
    Node<T> *currentOther = other.start->next;
    Node<T> *previous = newStart;

    // Докато не стигнем края на другия
    while (currentOther != nullptr)
    {   
        // Създаваме нова кутийка
        Node<T> *newNode = new Node<T>(currentOther->data);
        // Добавяме я към текущия списък
        previous->next = newNode;
        // Местим указателите напред
        previous = newNode;
        currentOther = currentOther->next;
    }

    // Не забравяме и да "копираме" размера
    this->size = other.size;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
{
    copy(other);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    cleanup();
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (this != &other)
    {
        cleanup();
        copy(other);
    }

    return *this;
}

template <typename T>
T LinkedList<T>::head()
{
    if (start == nullptr)
        return T();

    return start->data;
}

template <typename T>
void LinkedList<T>::pushFront(const T &elem)
{
    // Създаваме новата кутия
    Node<T> *newNode = new Node<T>(elem, start);

    // Обновяваме началото на списъка
    start = newNode;

    // Увеличаваме размера
    size++;
}

template <typename T>
void LinkedList<T>::popFront()
{
    if (start == nullptr)
        return;

    // Запазваме връзка към първата кутия
    Node<T> *tmp = start;

    // Местим началото към следващата кутия
    start = start->next;
    
    // Намаляваме размера
    size--;

    // Освобождаваме паметта за старата първа кутия
    delete tmp;
}

template <typename T>
T LinkedList<T>::get(int index)
{

    if (index < 0 || index >= size)
        // Връщаме произволна стойност.
        // След няколко упражнения ще видим как да обработваме грешки по по-добър начин.
        return T();

    // Класическо обхождане на списъка.
    // Почваме от началото
    Node<T> *current = start;
    int i = 0;

    while (i < index)
    {   
        // И на всяка стъпка скачаме към следващата кутия
        current = current->next;
        i++;
    }

    return current->data;
}

template <typename T>
void LinkedList<T>::pushBack(const T &elem)
{
    // Имайки вече функции, ги ползваме наготово
    insertAt(elem, size);
}

template <typename T>
void LinkedList<T>::popBack()
{
    // Имайки вече функции, ги ползваме наготово
    removeAt(size - 1);
}

template <typename T>
T LinkedList<T>::last()
{
    // Имайки вече функции, ги ползваме наготово
    return get(size - 1);
}

template <typename T>
void LinkedList<T>::insertAt(const T &elem, int index)
{
    if (index < 0 || index > size)
        return;

    if (index == 0)
    {
        pushFront(elem);
        return;
    }

    Node<T> *current = start;
    int i = 0;

    // Намираме кутийката на позиция index - 1
    while (i < index - 1)
    {
        current = current->next;
        i++;
    }

    // Създаваме нова кутийка между тази на index - 1 и index.
    Node<T> *newNode = new Node<T>(elem, current->next);
    current->next = newNode;
    size++;
}

template <typename T>
void LinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= size)
        return;

    if (index == 0)
    {
        popFront();
        return;
    }

    Node<T> *current = start;
    int i = 0;

    // Намираме кутийката на позиция index - 1
    while (i < index - 1)
    {
        current = current->next;
        i++;
    }


    Node<T> *nodeToDelete = current->next;
    // Свързваме кутийки index - 1 и index + 1
    current->next = current->next->next;
    // Изтриваме кутийка index
    delete nodeToDelete;
    size--;
}

template <typename T>
LinkedList<T> LinkedList<T>::reverse()
{
    if (start == nullptr)
        return LinkedList<T>();

    // Два указателя - единият който обхожда текушия списък, а другият ще ползваме, за да градим обърнатия списък
    Node<T> *current = start->next;
    Node<T> *reversedCurrent = new Node<T>(start->data);

    // Докато не стигнем до края на текущия списък
    while (current != nullptr)
    {
        // Вземаме текущата кутийка и я слагаме най-отпред в резултата
        Node<T> *newNode = new Node<T>(current->data, reversedCurrent);
        reversedCurrent = newNode;
        current = current->next;
    }

    return LinkedList<T>(reversedCurrent, size);
}

template <typename T>
template <typename U>
LinkedList<U> LinkedList<T>::map(std::function<U(T)> f)
{
    if (start == nullptr)
        return LinkedList<U>();

    // Подобна имплементация на copy метода с разликата, че данните, които слагаме в новите кутийки са
    // резултат от изпълнението на функцията f
    Node<T> *current = start->next;
    Node<U> *newStart = new Node<U>(f(start->data));
    Node<U> *resultCurrent = newStart;

    while (current != nullptr)
    {
        Node<U> *newNode = new Node<U>(f(current->data));
        resultCurrent->next = newNode;
        resultCurrent = newNode;
        current = current->next;
    }

    return LinkedList<U>(newStart, size);
}

template <typename T>
LinkedList<T> mergeLists(const LinkedList<T> &first, const LinkedList<T> &second)
{
    if (first.start == nullptr)
        return second;

    if (second.start == nullptr)
        return first;

    // 4 указателя:
    // един, който върви по първия списък
    // един, който върви по втория списък
    // един, който върви по резултатния списък
    // един, в който ще запазим началото на резултата
    Node<T> *currentFirst;
    Node<T> *currentSecond;
    Node<T> *newStart;
    Node<T> *resultCurrent;

    // Първо трябва да определим началния елемент на първия списък
    if (first.start->data > second.start->data)
    {
        currentFirst = first.start;
        currentSecond = second.start->next;
        newStart = new Node<T>(second.start->data);
        resultCurrent = newStart;
    }
    else
    {
        currentFirst = first.start->next;
        currentSecond = second.start;
        newStart = new Node<T>(first.start->data);
        resultCurrent = newStart;
    }

    // След това обхождаме двата входни списъка, докато не стигнем края на единия
    while (currentFirst != nullptr && currentSecond != nullptr)
    {
        // Определяме от кой списък да изградим текущия елемент на резултата
        if (currentFirst->data > currentSecond->data)
        {
            Node<T> *newNode = new Node<T>(currentSecond->data);
            resultCurrent->next = newNode;
            resultCurrent = newNode;
            currentSecond = currentSecond->next;
        }
        else
        {
            Node<T> *newNode = new Node<T>(currentFirst->data);
            resultCurrent->next = newNode;
            resultCurrent = newNode;
            currentFirst = currentFirst->next;
        }
    }

    // Когато стигнем краят на един от двата входни списъка, трябва само да изкопираме останалата част от другия списък
    Node<T> *remaining;
    if (currentFirst == nullptr)
        remaining = currentSecond;
    else
        remaining = currentFirst;

    while (remaining != nullptr)
    {
        Node<T> *newNode = new Node<T>(remaining->data);
        resultCurrent->next = newNode;
        resultCurrent = newNode;
        remaining = remaining->next;
    }

    return LinkedList<T>(newStart, first.size + second.size);
}
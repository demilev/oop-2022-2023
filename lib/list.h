#pragma once

#include <functional>

template <typename T>
class Node
{
public:
    T data;
    Node *next;

    Node();
    Node(const T &);
    Node(const T &, Node *);
};

template <typename T>
class LinkedList
{
private:
    Node<T> *start;
    int size;

    void cleanup();
    void copy(const LinkedList<T> &);

public:
    LinkedList();
    LinkedList(Node<T> *, int);
    LinkedList(const LinkedList<T> &);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &);

    int getSize();

    void pushFront(const T &);
    void popFront();

    T head();
    T last();
    T get(int);

    void pushBack(const T &);
    void popBack();

    void insertAt(const T &, int);
    void removeAt(int);

    LinkedList<T> reverse();

    template <typename U>
    LinkedList<U> map(std::function<U(T)>);

    template <typename U>
    friend LinkedList<U> mergeLists(const LinkedList<U> &, const LinkedList<U> &);
};

template <typename T>
Node<T>::Node() : data(), next(nullptr) {}

template <typename T>
Node<T>::Node(const T &data) : Node(data, nullptr) {}

template <typename T>
Node<T>::Node(const T &data, Node *next) : data(data), next(next) {}

template <typename T>
LinkedList<T>::LinkedList() : LinkedList<T>(nullptr, 0) {}

template <typename T>
LinkedList<T>::LinkedList(Node<T> *start, int size) : start(start), size(size) {}

template <typename T>
void LinkedList<T>::cleanup()
{
    if (start == nullptr)
        return;

    Node<T> *current = start;
    Node<T> *child = current->next;

    while (current != nullptr)
    {
        delete current;

        current = child;
        if (child != nullptr)
            child = child->next;
    }
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T> &other)
{
    if (other.start == nullptr)
    {
        this->start = nullptr;
        return;
    }

    Node<T> *newStart = new Node<T>(other.start->data);
    this->start = newStart;

    Node<T> *currentOther = other.start->next;
    Node<T> *previous = newStart;

    while (currentOther != nullptr)
    {   
        Node<T> *newNode = new Node<T>(currentOther->data);
        previous->next = newNode;
        previous = newNode;
        currentOther = currentOther->next;
    }

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
int LinkedList<T>::getSize()
{
    return this->size;
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
    Node<T> *newNode = new Node<T>(elem, start);

    start = newNode;

    size++;
}

template <typename T>
void LinkedList<T>::popFront()
{
    if (start == nullptr)
        return;

    Node<T> *tmp = start;

    start = start->next;
    
    size--;

    delete tmp;
}

template <typename T>
T LinkedList<T>::get(int index)
{

    if (index < 0 || index >= size)
        return T();

    Node<T> *current = start;
    int i = 0;

    while (i < index)
    {   
        current = current->next;
        i++;
    }

    return current->data;
}

template <typename T>
void LinkedList<T>::pushBack(const T &elem)
{
    insertAt(elem, size);
}

template <typename T>
void LinkedList<T>::popBack()
{
    removeAt(size - 1);
}

template <typename T>
T LinkedList<T>::last()
{
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

    while (i < index - 1)
    {
        current = current->next;
        i++;
    }

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

    while (i < index - 1)
    {
        current = current->next;
        i++;
    }


    Node<T> *nodeToDelete = current->next;
    current->next = current->next->next;
    delete nodeToDelete;
    size--;
}

template <typename T>
LinkedList<T> LinkedList<T>::reverse()
{
    if (start == nullptr)
        return LinkedList<T>();

    Node<T> *current = start->next;
    Node<T> *reversedCurrent = new Node<T>(start->data);

    while (current != nullptr)
    {
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

    Node<T> *currentFirst;
    Node<T> *currentSecond;
    Node<T> *newStart;
    Node<T> *resultCurrent;

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

    while (currentFirst != nullptr && currentSecond != nullptr)
    {
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
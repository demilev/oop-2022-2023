#include <iostream>
#include "todo.h"

void Task::cleanup()
{
    delete[] name;
}

void Task::copy(const Task &other)
{
    duration = other.duration;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

Task::Task()
{
    name = nullptr;
    duration = 0;
}

Task::Task(const Task &other)
{
    copy(other);
}

Task::~Task()
{
    cleanup();
}

Task &Task::operator=(const Task &other)
{
    if (this != &other)
    {
        cleanup();
        copy(other);
    }

    return *this;
}

Task::Task(const char *name, int duration)
{
    this->duration = duration;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Task::print()
{
    std::cout << "Task: " << name << std::endl;
    std::cout << "Duration in hours: " << duration << std::endl;
}

bool Task::operator==(const Task &other)
{
    return strcmp(name, other.name) == 0;
}

void TODOList::print()
{
    std::cout << "The list has " << tasks.getSize() << " tasks" << std::endl;
    for (int i = 0; i < tasks.getSize(); i++)
    {
        std::cout << "Task " << i << ":" << std::endl;
        tasks.get(i).print();
    }
}

void TODOList::addTask(const Task &task)
{
    tasks.add(task);
}

void TODOList::removeTask(const Task &task)
{

    int taskIndex = tasks.find(task);

    if (taskIndex >= 0)
    {
        tasks.removeAtIndex(taskIndex);
    }
}

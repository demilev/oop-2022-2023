#include <iostream>
#include "task.h"

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

int Task::getDuration()
{
    return duration;
}

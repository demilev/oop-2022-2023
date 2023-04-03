#pragma once

#include "vector.h"

class Task
{
private:
    char *name;
    int duration;

    void cleanup();
    void copy(const Task &);

public:
    Task();
    Task(const char *name, int duration);
    Task(const Task &);

    ~Task();

    Task &operator=(const Task &);

    void print();

    bool operator==(const Task &other);
};

class TODOList
{
private:
    Vector<Task> tasks;

public:
    void print();

    void addTask(const Task &);

    void removeTask(const Task &);
};

#pragma once

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

    int getDuration();
};

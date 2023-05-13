#pragma once

// Ще използваме класове от стандартната библиотека
#include <string> // Клас, представляващ символен низ. Аналог на char[]
#include <vector> // Клас, представляващ динамичен масив. Аналог на класа Vector, който вече имплементирахме

// Интерфейс, описващ един образователен ресурс
class LearningResource
{
public:
    // Виртуални методи с базовата функционалност
    virtual int duration() = 0;
    virtual std::string details() = 0;

    // Виртуален метод за клониране
    virtual LearningResource *clone() = 0;

    // Шом имаме клониране, имаме и виртуален деструктор. За класовете наследници, в които не го имплементираме, ще получим имплементация по подразбиране
    virtual ~LearningResource() = default;
};

// Наследник, представляващ видео урок
class VideoLesson : public LearningResource
{
private:
    int length;
    std::string title;

public:
    VideoLesson(int, std::string);
    int duration();
    std::string details();
    LearningResource *clone();
};

// Наследник, представляващ тест
class Exam : public LearningResource
{
private:
    int questions;
    std::string topic;

public:
    Exam(int, std::string);
    int duration();
    std::string details();
    LearningResource *clone();
};

// Наследник, представляващ съвкупност от ресурси
class Course : public LearningResource
{
private:
    std::vector<LearningResource *> resources;

public:
    int duration();
    std::string details();
    void addResource(LearningResource *resource);
    LearningResource *clone();
    ~Course();
};

// Функция за сортиране на ресурси по тяхната дължина.
// Забележете, че параметърът се подава по референция, защото ще го променяме
void sortResources(std::vector<LearningResource *> &);
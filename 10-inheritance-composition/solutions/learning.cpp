#include "learning.h"

#include <algorithm>
#include <string>
#include <vector>


// Използваме копи конструктора на класа string
VideoLesson::VideoLesson(int length, std::string title) : length(length), title(title) {}

int VideoLesson::duration()
{
    return length;
}

std::string VideoLesson::details()
{
    return title;
}

LearningResource *VideoLesson::clone()
{
    return new VideoLesson(length, title);
}

Exam::Exam(int questions, std::string topic) : questions(questions), topic(topic) {}

int Exam::duration()
{
    return questions * 5;
}

std::string Exam::details()
{
    // Изпозлваме удобния оператор + за конкатениране на string-ове.
    // Използвмае и удобен метод за конвертиране от число към string(нещо, което сме правили в първия семестър)
    return topic + ", Questions " + std::to_string(questions);
}

LearningResource *Exam::clone()
{
    return new Exam(questions, topic);
}

int Course::duration()
{
    int total = 0;

    // Продължителността на един курс е сума от продължителността на ресурсите в него
    for (LearningResource *resource : resources)
    {
        total += resource->duration();
    }

    return total;
}

std::string Course::details()
{

    std::string result;

    // Детайлите на един курс са конкатенация от детайлите на ресурсите в него
    for (LearningResource *resource : resources)
    {
        result += resource->details();
        result += "\n";
    }

    return result;
}

LearningResource *Course::clone()
{
    Course *result = new Course();

    // Важно е да клонираме и всеки един от ресурсите. Това ще се случи с помощтта на addResource
    for (LearningResource *resource : resources)
        result->addResource(resource);

    return result;
}

void Course::addResource(LearningResource *resource)
{
    // Добавяме копие на параметъра, който е подаден на метода.
    // Ние ще се грижим за жизнения цикъл на копието - заделяне и освобождаване на памет.
    resources.push_back(resource->clone());
}

Course::~Course()
{  
    // Зачистваме паметта заделена за ресурсите
    for (LearningResource *resource : resources)
        delete resource;
}

// Когато работим с класове от стандартната библиотека, получаваме много удобства на готово,
// за които има документация и примери в интернет - https://en.cppreference.com/w/cpp/algorithm/sort
void sortResources(std::vector<LearningResource *> &resources)
{
    // Първият аргумент е итератор към началото, вторият аргумент е итератор към края, третият аргумент е функция, която указва правилото за сравняване на два елемента
    std::sort(resources.begin(), resources.end(), [](LearningResource *first, LearningResource *second) -> bool
              { return first->duration() < second->duration(); });
}
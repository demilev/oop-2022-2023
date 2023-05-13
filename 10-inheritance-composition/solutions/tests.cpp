#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../lib/doctest.h"
#include "learning.h"
#include <vector>

// Тест за създаване на видео урок и използване на базовите му методи
TEST_CASE("testing the creation of a video lesson")
{
    VideoLesson vl(30, "test lesson");

    // Изпозлваме оператор == на класа string за сравняване
    CHECK(vl.details() == "test lesson");
    CHECK(vl.duration() == 30);
}

// Тест за създаване на тест и използване на базовите му методи
TEST_CASE("testing the creation of an exam")
{
    Exam e(10, "test exam");

    CHECK(e.details() == "test exam, Questions 10");
    CHECK(e.duration() == 50);
}

// Тест за създаване на курс и добавяне на ресурси
TEST_CASE("testing the creation of a course")
{
    Course c;

    VideoLesson vl(30, "test lesson");
    Exam e(10, "test exam");

    c.addResource(&vl);
    c.addResource(&e);

    CHECK(c.details() == "test lesson\ntest exam, Questions 10\n");
    CHECK(c.duration() == 80);
}

// Тест за сортиране на ресурси
TEST_CASE("testing the sorting of resources")
{
    Course c;

    VideoLesson vl(30, "test lesson");
    Exam e(10, "test exam");

    c.addResource(&vl);
    c.addResource(&e);

    std::vector<LearningResource *> resources = {&c, &vl, &e};
    std::vector<LearningResource *> sorted = {&vl, &e, &c};

    sortResources(resources);

    // Използваме оператор == на класа vector за сравняване
    CHECK(resources == sorted);
}

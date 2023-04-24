#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"

#include "list.h"

// Тест за създаване на Node
TEST_CASE("testing the creation of a Node")
{
    // Създаваме Node с конструктора му с един параметър
    Node<int> node(5);

    // Проверяваме, че данните, които държи са тези, които сме подали в конструктора 
    CHECK(node.data == 5);
    // Проверяваме, че няма наследник
    CHECK(node.next == nullptr);
}

// Тест за добавяне на елемент в началото на списък
TEST_CASE("testing the insertion of a Node")
{
    // Създаваме празен списък
    LinkedList<int> list;

    // Добавяме му един елемент в началото
    list.pushFront(5);
    // Проверяваме, че в началото стои този елемент
    CHECK(list.head() == 5);

    // Добавяме нов елемент в началото
    list.pushFront(6);
    // Проверяваме, че в началото стои този елемент
    CHECK(list.head() == 6);
}

// Тест за премахване на елемент от началото на списък
TEST_CASE("testing the removing of a Node")
{
    // Създаваме празен списък
    LinkedList<int> list;

    // Добавяме му два елемента в началото
    list.pushFront(5);
    list.pushFront(6);

    // Премахваме единия
    list.popFront();
    // Проверяваме, че другият е в началото на списъка
    CHECK(list.head() == 5);
}

// Тест за опит за премахване на елемент от празен списък
TEST_CASE("testing the removing of a Node in an empty list")
{
    // Създаваме празен списък
    LinkedList<int> list;
    // Опитваме се да премахнем елемент - тази операция не трябва да прави нищо в такъв случай
    list.popFront();

    // Добавяме един елемент и проверяваме, че е на първа позиция
    list.pushFront(5);
    CHECK(list.head() == 5);
}

// Тест за достъпване на елемент по индес
TEST_CASE("testing the accessing of elements in a LinkedList")
{
    // Създаваме списък и му добавяме няколко елемента
    LinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    // Проверяваме, че елементите стоят на сътоветните индекси
    CHECK(list.get(0) == 8);
    CHECK(list.get(1) == 2);
    CHECK(list.get(2) == 6);
    CHECK(list.get(3) == 5);
}

// Тест за копиране на списък
TEST_CASE("testing the copying of LinkedList")
{
    // Създаваме списък и му добавяме няколко елемента
    LinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    // Създаваме копие на списъка
    LinkedList<int> copyList(list);

    // Проверяваме, че действително е копие
    CHECK(copyList.get(0) == 8);
    CHECK(copyList.get(1) == 2);
    CHECK(copyList.get(2) == 6);
    CHECK(copyList.get(3) == 5);

    // Правим промяна по копието
    copyList.pushFront(10);

    // Проверяваме, че само копието се е променило
    CHECK(list.get(0) == 8);
    CHECK(copyList.get(0) == 10);
}

// Тест за добавяне на елемент в края на списък
TEST_CASE("testing appending to a list")
{   
    // Създаваме празен списък
    LinkedList<int> list;

    // Добавяме му елемент в края
    list.pushBack(5);
    // Проверяваме, че последният и първият елемент съвпадата
    CHECK(list.last() == 5);
    CHECK(list.head() == 5);

    // Добавяме нов елемент в края
    list.pushBack(6);
    // Проверяваме, че последният елемент е променен, а първият не
    CHECK(list.last() == 6);
    CHECK(list.head() == 5);
}

// Тест за премахване на елемент от края на списък
TEST_CASE("testing removing the last element of a list")
{
    // Създаваме списък и му добавяме няколко елемента
    LinkedList<int> list;

    list.pushBack(5);
    list.pushBack(6);
    list.pushBack(3);
    CHECK(list.last() == 3);

    // Махаме последния и виждаме, че новият последен е променен
    list.popBack();
    CHECK(list.last() == 6);
}

// Тест за добавяне на елемент на произволна позиция
TEST_CASE("testing random insert in a list")
{
    
    // Създаваме списък и му добавяме няколко елемента
    LinkedList<int> list;

    list.pushBack(5);
    list.pushBack(6);
    list.pushBack(3);
    
    // Добавяме елемент на индекс 2 и проверяваме, че е действително там
    list.insertAt(-5, 2);
    CHECK(list.get(2) == -5);
}


// Тест за премахване на елемент на произволна позиция
TEST_CASE("testing random delete in a list")
{
    // Създаваме списък и му добавяме няколко елемента
    LinkedList<int> list;

    list.pushBack(5);
    list.pushBack(6);
    list.pushBack(3);

    // Премахваме елемента на индекс 1
    list.removeAt(1);

    // Виждаме, че списъкът вече съдържа само другите два елемента
    CHECK(list.get(0) == 5);
    CHECK(list.get(1) == 3);
}

// Тест за обръщане на свързан списък
TEST_CASE("testing reversing of a LinkedList")
{   
    // Създаваме списък и му добавяме няколко елемента
    LinkedList<int> list;

    list.pushFront(5);
    list.pushFront(6);
    list.pushFront(2);
    list.pushFront(8);

    // Създаваме обърнатата му версия
    LinkedList<int> reversed = list.reverse();

    // Проверяваме, че наредбата е обърната
    CHECK(reversed.get(0) == 5);
    CHECK(reversed.get(1) == 6);
    CHECK(reversed.get(2) == 2);
    CHECK(reversed.get(3) == 8);
}

// Тест за прилагане на операция map
TEST_CASE("testing map of a LinkedList")
{
    // Създаваме списък и му добавяме няколко елемента
    LinkedList<int> list;

    list.pushFront(19);
    list.pushFront(18);
    list.pushFront(4);
    list.pushFront(19);

    // Създаваме списък от символи чрез map функцията
    LinkedList<char> letters = list.map<char>([](int x) -> char { return 'a' + x; });

    // Проверяваме, че елементите на резултата са с правилни стойности
    CHECK(letters.get(0) == 't');
    CHECK(letters.get(1) == 'e');
    CHECK(letters.get(2) == 's');
    CHECK(letters.get(3) == 't');
}

// Тест за обединяване на два сортирани свързани списъка
TEST_CASE("testing the merging of two LinkedList")
{
    // СЪздаваме два списъка и им добавяме няколко елемента в сортиран ред
    LinkedList<int> first;
    LinkedList<int> second;

    first.pushBack(1);
    first.pushBack(5);
    first.pushBack(12);
    first.pushBack(33);

    second.pushBack(-5);
    second.pushBack(2);
    second.pushBack(4);

    // Обединяваме ги
    LinkedList<int> result = mergeLists(first, second);

    // Проверяваме, че резултатът е сортиран
    CHECK(result.get(0) == -5);
    CHECK(result.get(1) == 1);
    CHECK(result.get(2) == 2);
    CHECK(result.get(3) == 4);
    CHECK(result.get(4) == 5);
    CHECK(result.get(5) == 12);
    CHECK(result.get(6) == 33);
}
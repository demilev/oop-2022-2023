# Тема 6, Ламбда функции, 04.04.2023

## Declaration vs Definition

```c++
int f();

double g(int, bool);

class A;

class B
{
private:
    int x;
public:
    B();
    int plus(int);
};
```

```c++
int f()
{
    return 5;
}

double g(int x, bool p)
{
    if (p)
        return 2.5 * x;
    return 3.5 * x;
}

class A
{
public:
    void print()
    {
        std::cout << "Hey A" << std::endl;
    }
};

B::B(): x(0) {}

int B::plus(int y)
{
    return x + y;
}
```

## Разделно компилиране

<br/>

![Diagram](content/cpp-program-diagram.png)

<br/>

<br/>

![Diagram Extended](content/cpp-program-diagram-extended.png)

<br/>

https://domiyanyue.medium.com/c-development-tutorial-2-compile-multiple-files-1-compiling-process-basics-41fba37eed6c

## std::function

```c++
int func(int y)
{
    return y + 5;
}

class A
{
public:
    int operator()(int y) {
        return y + 10;
    }
};

int main()
{
    A aObject;

    std::function<int(int)> fn1 = func;
    std::function<int(int)> fn2 = aObject;

    std::cout << fn1(3) << std::endl;
    std::cout << fn2(4) << std::endl;

    return 0;
}
```

## Ламбда израз

```c++
int main()
{
    double a = 3;
    double b = 4;

    std::function<int(int)> fn = [](int x) -> int { return x + 5; };
    std::cout << fn(1) << std::endl;

    // Копие на a ще бъде достъпно в тялото на функцията
    std::function<int(int)> fn1 = [a](int x) -> int { return x + 5; };
    // Самото a ще бъде достъпно в тялото на функцията
    std::function<int(int)> fn2 = [&a](int x) -> int { return x + 5; };
    // Самото a и копие на b ще бъдат достъпни в тялото на функцията
    std::function<int(int)> fn3 = [&a](int x) -> int { return x + 5; };
    // Всичко в текущия контекст ще бъде достъпно като копие в тялото на функцията
    std::function<int(int)> fn4 = [=](int x) -> int { return x + 5; };
    // Всичко в текущия контекст ще бъде достъпно по референция в тялото на функцията
    std::function<int(int)> fn5 = [&](int x) -> int { return x + 5; };

    return 0;
}
```

## Задачи

### Зад. 1 - [Решение](./solutions/lambdas.cpp)

Имплементирайте функция, която

* приема булева функция `f` и която връща друга фунцкия `g`, която е отрицанието на f(т.е. `g(x) = true <=> f(x) = false` и `g(x) = false <=> f(x) = true`)
* приема две функции(`f`, `g`) и връща функция(`h`), която е тяхна композиция (`h(x) = f(g(x))`)
* приема булева функция(`p`) и две други функции(`f`, `g`) и която връща функция(`h`), която прилага `f`, ако `p` е истина и `g` в противен случай(т.е. `h(x) = f(x), ако p(x) = true` и `h(x) = g(x), ако p(x) = false`)

### Зад. 2 - [Решение](./solutions/vector/)

Разширете класа `Vector` от миналата седмица със следните методи:

* `find(std::function<bool(T)> p)`, която връща индекса на първия елемент в масива, който отговаря на предиката `p`
* `exists(std::function<bool(T)> p)`, която връща дали съществува елемент в масива, който отговаря на предиката `p`
* `map(std::function<U(T)> f)`, която връща нов `Vector<U>`, елементите на който са получени от елементите на текущия след прилагането на фунцкията `f` върху всеки един от тях
* `foldLeft(R result, std::function<R(R, E)> f)`, която обхожда масива и прилага функцията `f` върху резултата от последното й прилагане и текущия елемент
* `foldRight(R result, std::function<R(R, E)> f)`, която обхожда масива отзад напред и прилага функцията `f` върху резултата от последното й прилагане и текущия елемент
* `flatMap(std::function<Vector<U>(T)> f)`, която връща нов `Vector<U>`, елементите на който са получени от елементите на текущия след прилагането на фунцкията `f` върху всеки един от тях

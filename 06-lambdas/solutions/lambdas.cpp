#include <iostream>
#include <functional>


/*
    Имплементирайте функция, която
        * приема булева функция `f` и която връща друга фунцкия `g`, която е отрицанието на f(т.е. `g(x) = true <=> f(x) = false` и `g(x) = false <=> f(x) = true`)
        * приема две функции(`f`, `g`) и връща функция(`h`), която е тяхна композиция (`h(x) = f(g(x))`)
        * приема булева функция(`p`) и две други функции(`f`, `g`) и която връща функция(`h`), която прилага `f`, ако `p` е истина и `g` в противен случай(т.е. `h(x) = f(x), ако p(x) = true` и `h(x) = g(x), ако p(x) = false`)
*/


// negate е шаблонна функция, която приема параметът от тип std::function и връща като резултат друг std::function
template <typename T>
std::function<bool(T)> negate(std::function<bool(T)> f)
{   
    // Резултата ще изградим чрез ламбда израз.
    // "Хващаме" f от външния контекст, защото ще искаме да го ползваме в тялото на ламбдата.
    // Типът на ламбдата е T -> bool.
    // А в тялото просто извикваме f и връшаме негацията му.
    return [f](T x) -> bool
    {
        return !f(x);
    };
}

bool isPositive(int x)
{
    return x >= 0;
}

// composite е шаблонна функция, която приема два параметъра от тип std::function и връща като резултат друг std::function
template <typename T, typename U, typename H>
std::function<T(H)> composite(std::function<U(T)> f, std::function<H(U)> g)
{
    // Резултата ще изградим чрез ламбда израз.
    // "Хващаме" f и g от външния контекст, защото ще искаме да ги ползваме в тялото на ламбдата.
    // Типът на ламбдата е T -> H.
    // А в тялото просто извикваме f върху резултата от изпълнението на g.
    return [f, g](T x) -> H {
        return f(g(x));
    };
}

// composite е шаблонна функция, която приема три параметъра от тип std::function и връща като резултат друг std::function
template <typename T, typename U>
std::function<U(T)> ifFunction(std::function<bool(T)> p, std::function<U(T)> f, std::function<U(T)> g)
{
    // Резултата ще изградим чрез ламбда израз.
    // Използвайки "=" в capture list-a, "хващаме" всичко от външния контекст, защото ще искаме да ползваме p, f и g в тялото на ламбдата.
    // Типът на ламбдата е T -> U.
    // А в тялото просто извикваме f или g спрямо резултата от p.
    return [=](T x) -> U {
        if (p(x))
            return f(x);
        return g(x);
    };
}

int multiplyBy5(int x)
{
    return x * 5;
}

int sum3(int x)
{
    return x + 3;
}


int main()
{
    // Извикваме negate, за да получим функцията отрицание на isPositive 
    std::function<bool(int)> isNegative = negate<int>(isPositive);

    std::cout << isNegative(-5) << std::endl;
    
    std::cout << isPositive(-5) << std::endl;

    // Извикваме negate, за да получим функцията отрицание на ламбда израз, който описва функция, която прави проверка за четност
    std::function<bool(int)> isOdd = negate<int>([](int x) -> bool { return x % 2 == 0; });

    std::cout << isOdd(5) << std::endl;

    // композираме две от нашите функции
    std::function<int(int)> result = composite<int, int, int>(multiplyBy5, sum3);

    // композираме две ламбда функции
    std::function<int(int)> result1 = composite<int, int, int>(
        [](int x) -> int { return x + 5; },
        [](int x) -> int { return x * 7; }
    );

    std::cout << result(4) << std::endl;
    std::cout << result1(4) << std::endl;


    // Получаваме функция, която умножава едно число по 5, ако е положително или му прибавя 3 в противен случай
    std::function<int(int)> p = ifFunction<int, int>(isPositive, multiplyBy5, sum3);

    std::cout << p(4) << std::endl;
    std::cout << p(-10) << std::endl;

    return 0;
}
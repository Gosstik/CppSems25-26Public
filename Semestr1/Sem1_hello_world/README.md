# Семинар 1. Hello, world

## База C++ для контестов

- Функция `main`, `return 0`
- Объявление переменных (в том числе через запятую)
- Ввод-вывод значений (`std::cin`, `std::cout`)
- `using namespace std`, тогда можно писать `cin`, `cout` без префикса `std::`, но такое на ревью будут банить
- `%` (oстаток от деления), `/` (целочисленное деление), `<<` и `>>` (битовый сдвиг)
- `if`, `for` (`break` и `continue`, на примере арифм прогрессии), `while`, `do while`, `switch` (на примере кол-ва дней в месяце)
- Типы данных + `sizeof`
  - Целочисленные: `short`, `int`, `long`, `long long`.
  - Целочисленные беззнаковые: аналогичны обычным, с приставкой `unsigned` (e.g. `unsigned int`, `unsigned long`).
  - Целочисленные с фиксированным размером (`#include <cstdint>)`: `int16_t`, `int32_t`, `int64_t`. Для беззнаковых добавить `u`: `uint32_t`, `uint64_t`)
  - С плавающей точкой: `float`, `double`, `long double`
  - Числовые литералы: `1000000`, `1'000'000`, `24.5`, `2ll`, `3ull`, `1.0f`, `0b101`, `010`, `0xff`
  - Строковые литералы: `"Hello, world!"` (тип `const char[]`, обычно используют `const char*`)
  - Символьные литералы: `'a'`, `'\n'` (тип `char`)
- Неинициализированные переменные, переполнение (unsigned - модульная арифметика, signed - UB)
- Создание и передача аргументов в функцию, возвращаемое значение
- Области видимости переменных (`scope`)
- Создание нативных массивов `int arr[10];`, `int arr[] = {1, 2, 3}`, `int arr[5] = {1, 2, 3}`, `int arr[n];`;
- `std::vector` и его методы (`#include <vector>`):
  - `vector(size, default_value)`
  - `vector.[index]`
  - `push_back(value)`
  - `pop_back()`
  - `back()`
  - `front()`
  - `size()` + `resize(size)`
  - `capacity()` + `reserve(size)` (прим: можно сделать for + if и посмотреть, на каких индексах меняется capacity())
  - `shrink_to_fit()`
  - `empty()`
  - `clear()`
  - `vec2 = vec1`
- Создание двумерных массивов `std::vector<std::vector<int>>`, изменение размера (`assign`)
- `std::string` и его методы(`#include <string>`):
  - `string(size, char)`, `string(const char*)`
  - аналогичные `std::vector`
  - `+=`, `+` (использовать `reserve` !!!)
  - `substr(start_pos, count)`, `std::string::npos`
  - `find(string, start_pos)` + `rfind`
  - Сравнение строк
  - `std::cout << string`
- Преобразование строки в число (`#include <string>`): `stoi`, `stol`, `stoll`
- Преобразование числа в строку (`#include <string>`): `to_string`
- Считывание всей строки с потока ввода, включая пробельные символы (`#include <string>`): `std::getline(std::cin, string, '\n')`
- Передача в функцию по ссылке для изменения содержимого внутри
- Алгоритмы (`#include <algorithm>`)
  - Сортировка массивов: `std::sort(first, last, comparator)`
  - Разворот массива: `std::reverse(first, last)`
  - Поиск в массиве: `std::copy(first, last, destination)`
- Структуры данных:
  - Последовательные контейнеры:
    - `std::deque`: двусторонняя очередь
    - `std::forward_list`, `std::list`: односвязный и двусвязный списки
    - `std::stack`: стек
    - `std::queue`: очередь
  - Ассоциативные контейнеры:
    - `std::map`: сбалансированное дерево поиска
    - `std::unordered_map`: хеш-таблица
    - `std::set` и `std::unordered_set`: множество элементов

Несолжные задачи на практику:

- ArgMax массива (`argmax.cpp`)
- Общий префикс двух строк (`common_prefix.cpp`)
- Сумма цифр в числе (`sum_digits.cpp`)
- Подсчёт числа букв в тексте (`alphas_count.cpp`)
- Подсчёт числа слов в тексте (`word_count.cpp`)
- Целочисленный логарифм по основанию 2 (`int_log2.cpp`)
- Получить наибольшую степень двойки, меньшую данного числа (`max_power_of_2.cpp`)

## Компиляторы

Сейчас активно используются и поддерживаются 3 компилятора: `g++`, `clang++` и `msvc`. Последний из них широко используется на OS Windows, мы же в курсе будем полагаться только на первые 2. При установке компиляторов вам скорее всего будут встречаться `gcc` и `clang` вместо `g++`, `clang++` - это компиляторы для языка `C`, они поставляются вместе с компиляторами для `C++`.

Про установку свежих версий компиляторов можно почитать тут: [gcc](https://github.com/Gosstik/SoftDocs/blob/master/gcc/gcc-installation.md), [clang](https://github.com/Gosstik/SoftDocs/blob/master/clang/clang-installation.md).

Посмотреть, какую версию компилятора вы используете сейчас, можно с помощью флага `--version`:

```bash
g++ --version
readlink -f /bin/g++ # Посмотреть путь до файла, на который ссылается g++
```

**Важно**: версия компилятора != версия стандарта.

Команда для компиляции программы и некоторые её флаги:

```bash
g++ main.cpp # Обычная компиляция, на выходе получаем a.out
./a.out # Запускаем скомпилированную программу

g++ main.cpp -o main.exe # Вместо a.out результат будет в main.exe
./main.exe

g++ -std=c++20 main.cpp -o main.out # Явно указываем, какой стандарт использовать
```

## Links

Онлайн компилятор: [godbolt](https://godbolt.org/).

IDE:

- [VScode](https://code.visualstudio.com/) - гарантировано бесплатный, но много чего придётся ставить руками
- [CLion](https://www.jetbrains.com/clion/#) - все базовые настройки инкапсулирует в себе, прост в освоении для начинающих (для скачивания скорее всего нужен VPN)

OS:

- [Dual Boot](https://github.com/Gosstik/SoftDocs/blob/master/dual-boot.md)
- [Как жить без линукса](https://docs.google.com/document/d/1CUu8SE_aymzAsIvkkYvwEI2xi-twdfpg_7xYd8dWXbM/edit?usp=sharing)

Гипервизоры для виртуальных машин:

- [VMware Workstation Pro for PC (official, free for personal use)](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion#product-overview)
- [VirtualBox](https://www.virtualbox.org/)

Основы C++ (+ литература):

- [Яндекс handbook](https://education.yandex.ru/handbook/cpp)
- [Bjarne Stroustrup, The C++ Programming Language (4th Edition)](https://agorism.dev/book/c%2B%2B/Stroustrup%20B.%20-%20The%20C%2B%2B%20Programming%20Language%2C%204th%20Edition-Addison%20Wesley%20%282013%29.pdf)
- [cppreference](https://en.cppreference.com)
- [stackoverflow](https://stackoverflow.com/questions)

Стандарты:

- [Драфты стандарта разных лет](https://www.open-std.org/jtc1/sc22/wg21/docs/standards)
- [Драфт C++20](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/n4849.pdf)
- [Драфт C++23](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf)

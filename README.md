# Translator
НГТУ, ФПМИ 6 семестр. Методы трансляции

## Практическое задание № 1

ПРОЕКТИРОВАНИЕ И РЕАЛИЗАЦИЯ ТАБЛИЦ, ИСПОЛЬЗУЕМЫХ В ТРАНСЛЯТОРЕ

### 1. Цель работы

Получить представление о видах таблиц, используемых при трансляции программ. Изучить множество операций с таблицами и особенности реализации этих операций для таблиц, используемых на этапе лексического анализа. Реализовать классы таблиц, используемых сканером.

### 2. Задание

+ разработать структуру постоянных таблиц для хранения алфавита языка, зарезервированных слов, знаков операций, разделителей и пр.;
+ реализовать для постоянных таблиц алгоритм поиска элемента в упорядоченной таблице;
+ разработать структуру переменных таблиц с вычисляемым входом для хранения идентификаторов и констант (вид хеш-функции и метод рехеширования задает разработчик);
+ реализовать для переменных таблиц алгоритмы поиска/добавления лексемы, поиска/добавления атрибутов лексемы;
+ разработать программу для тестирования и демонстрации работы программ пп.1-3.

### 3. Вариант

Подмножество языка С++ включает:

+ данные типа int;
+ инструкции описания переменных;
+ операторы присваивания в любой последовательности;
+ операции +, –, *, ==, != , <, >

### 4. Исходные данные

Исходными данными для постоянных таблиц является файл, где перечислены элементы этих таблиц. В файле каждый идентификатор начинается с новой строки. Добавление элементов в переменные таблицы происходит по ходу работы программы, используя в качестве ключа идентификатор элементов. На количество элементов в таблицах не накладывается никаких программных ограничений, кроме аппаратных ограничений компьютера.
Вычисления хэша производится по первому символу идентификатора, в следующем порядке: сначала идут цифры, затем строчные буквы латинского алфавита, затем заглавные буквы латинского алфавита.

## Практическое задание № 2

### 1. Цель работы

Изучить методы лексического анализа. Получить представление о методах обработки лексических ошибок. Научится проектировать сканер на основе детерминированных конечных автоматов.

### 2. Задание

Входные данные представляют собой имя файла, содержавшего исходный код, а так же имена файла токенов и файла ошибок. Результатам работы программы являются два файла – файл токенов и файл ошибок.

#ifndef TABLE_VAR_H_INCLUDED
#define TABLE_VAR_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include "lexeme.h"

using namespace std;

// Класс переменных таблиц
class table_var{
private:
    // Размер таблицы
    int hashnum;
    // Указатель на массив цепочек
    vector<lexeme> *table;
    // Подсчет хэша
    int get_hash(string name);
    // Подсчет номера в цепочке
    int get_chain(string name);
public:
    // Конструктор с размером таблицы по умолчанию
    table_var();
    // Конструктор с пользовательским размером таблицы
    table_var(int new_hashnum);
    // Деструктор
    ~table_var();
    // Определение хэша и номера в цепочке
    bool get_location(string name, int &hash, int &chain);
    // Проверка есть ли элемент в таблице
    inline bool check(string name);
    // Добавление нового имени идентификатора или значения константы
    bool add(string name);
    // Задание типа по хэшу и номеру в цепочке
    bool set_type(int hash, int chain, int type);
    // Задание типа по имени идентификатора или значению константы
    bool set_type(string name, int type);
    // Задание флага инициализации по хэшу и номеру в цепочке
    bool set_is_init(int hash, int chain, bool is_init);
    // Задание флага инициализации по имени идентификатора или значению константы
    bool set_is_init(string name, bool is_init);
    // Получение структуры lexeme по хэшу и номеру в цепочке
    bool get_lexeme(int hash, int chain, lexeme &lexeme);
    // Получение структуры lexeme по имени идентификатора или значению константы
    bool get_lexeme(string name, lexeme &lexeme);
    // Отладочная печать
    void debug_print(ostream& stream);
};

#endif // TABLE_VAR_H_INCLUDED

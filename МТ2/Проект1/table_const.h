#ifndef TABLE_CONST_H_INCLUDED
#define TABLE_CONST_H_INCLUDED
#include <fstream>
#include <string>
#include <set>

using namespace std;

// Класс постоянных таблиц
template <typename type> class table_const{
private:
    set<type> table;
public:
    // Конструктор по умолчанию
    table_const() {}
    // Деструктор
    ~table_const(){
        table.clear();
    }
    // Добавление элемента в таблицу
    inline void add(type elem){
        table.insert(elem);
    }
    // Чтение таблицы из файла
    bool read_file(string name){
        ifstream fs(name.c_str(), ios::in);
        if(!fs.is_open())
            return false;
        type elem;
        while (!fs.eof())
        {
            fs >> elem;
            add(elem);
        }
        return true;
    }
    // Проверка есть ли элемент в таблице
    bool check(type elem){
        typename set<type>::iterator it = table.find(elem);
        if(it == table.end()) 
            return false;
        return true;
    }
    // Поиск номера по значению
    bool get_num(type elem, int &num){
        if(!check(elem))
            return false;
        num = distance(table.begin(), table.find(elem));
        return true;
    }
    // Поиск значения по номеру
    bool get_val(int num, type &elem){
        if(num < 0 || num >= table.size())
            return false;
        typename set<type>::iterator it = table.begin();
        for(int i = 0; i < num; i++)
            it++;
        elem = *it;
        return true;
    }
};

#endif // TABLE_CONST_H_INCLUDED

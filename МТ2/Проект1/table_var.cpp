#include "table_var.h"

// Размер хэш-таблицы по умолчанию
#define default_hashnum 100

// Подсчет хэша
int table_var::get_hash(string name){
    int hash = 0;
    for(int i = 0; i < name.size(); i++)
        hash += name[i];
    return hash % hashnum;
}

// Подсчет номера в цепочке
int table_var::get_chain(string name){
    for(int i = 0, h = get_hash(name); i < table[h].size(); i++)
        if(name == table[h][i].name) return i;
    return -1;
}

// Конструктор с размером таблицы по умолчанию
table_var::table_var(){
    hashnum=default_hashnum;
    table = new vector<lexeme> [hashnum];
}

// Конструктор с пользовательским размером таблицы
table_var::table_var(int new_hashnum){
    hashnum=new_hashnum;
    table = new vector<lexeme> [hashnum];
}

// Деструктор
table_var::~table_var(){
    for(int i = 0; i < hashnum; i++)
        table[i].clear();
    delete [] table;
}

// Проверка есть ли элемент в таблице
inline bool table_var::check(string name){
    if(get_chain(name) != -1) return true;
    return false;
}

// Добавление нового имени идентификатора или значения константы
bool table_var::add(string name){
    if(check(name)) return false;
    int h = get_hash(name);
    table[h].push_back(lexeme(name));
    return true;
}

// Задание типа по хэшу и номеру в цепочке
bool table_var::set_type(int hash, int chain, int type){
    if(chain == -1) return false;
    table[hash][chain].type = type;
    return true;
}

// Задание типа по имени идентификатора или значению константы
bool table_var::set_type(string name, int type){
    int hash = get_hash(name), chain = get_chain(name);
    return set_type(hash, chain, type);
}

// Задание флага инициализации по хэшу и номеру в цепочке
bool table_var::set_is_init(int hash, int chain, bool is_init){
    if(chain == -1) return false;
    table[hash][chain].is_init = is_init;
    return true;
}

// Задание флага инициализации по имени идентификатора или значению константы
bool table_var::set_is_init(string name, bool is_init){
    int hash = get_hash(name), chain = get_chain(name);
    return set_is_init(hash, chain, is_init);
}

// Определение хэша и номера в цепочке
bool table_var::get_location(string name, int &hash, int &chain){
    int h = get_hash(name), c = get_chain(name);
    if(chain == -1) return false;
    hash = h;
    chain = c;
    return true;
}

// Получение структуры lexeme по хэшу и номеру в цепочке
bool table_var::get_lexeme(int hash, int chain, lexeme &lexeme){
    if(chain == -1) return false;
    lexeme = table[hash][chain];
    return true;
}

// Получение структуры lexeme по имени идентификатора или значению константы
bool table_var::get_lexeme(string name, lexeme &lexeme){
    int hash = get_hash(name), chain = get_chain(name);
    return get_lexeme(hash, chain, lexeme);
}

// Отладочная печать
void table_var::debug_print(ostream& stream){
    for(int i = 0; i < hashnum; i++){
        if(table[i].size()){
            stream << i << ":\t[ ";
            for(int j = 0; j < table[i].size(); j++){
                stream << table[i][j].name;
                switch(table[i][j].type){
                case 0:
                    stream << "\tnotype";
                    break;
                case 1:
                    stream << "\tint";
                    break;
                }
                stream << table[i][j].is_init << "\tinit={";
                if(j != table[i].size() - 1) stream << "},\t";
                else stream << "}";
            }
            stream << " ]" << endl;
        }
    }
}

#undef default_hashnum

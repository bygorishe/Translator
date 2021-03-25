#include "lexeme.h"

// Конструктор по умолчанию
lexeme::lexeme() {}

// Конструктор с заданием имени идентификатора или значения константы
lexeme::lexeme(string new_name){
    name = new_name;
    type = 0;
    is_init = false;
}

// Деструктор
lexeme::~lexeme() {}

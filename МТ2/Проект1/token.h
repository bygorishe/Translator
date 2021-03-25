#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

// Класс токенов
class token{
public:
    int table; // Номер таблицы
    int place; // Положение в таблице
    int chain; // Положение в цепочке
    // Конструкторы
    token();
    token(int table_, int place_, int chain_);
    // Ввод-вывод токенов
    friend istream& operator >> (istream& istream_, token& token_);
    friend ostream& operator << (ostream& ostream_, const token& token_);
};

#endif // TOKEN_H_INCLUDED

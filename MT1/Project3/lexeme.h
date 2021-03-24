#ifndef LEXEME_H_INCLUDED
#define LEXEME_H_INCLUDED
#include <string>
#include <vector>
using namespace std;
// Класс для хранения идентификаторов и констант
class lexeme
{
public:
	// Имя идентификатора или значение константы
	string name;
	// Тип, 0 - не определен, 1 - int
	int type;
	// Массив флагов "илициализировано ли" 
	bool is_init;
	// Конструктор по умолчанию
	lexeme();
	// Конструктор с заданием имени идентификатора или значения константы
	lexeme(string new_name);
	// Деструктор
	~lexeme();
};
#endif // LEXEME_H_INCLUDED
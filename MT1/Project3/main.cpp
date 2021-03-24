#include <iostream>
#include <stdio.h>
#include "table_const.h"
#include "table_var.h"
using namespace std;
int main()
{
	table_const<string> separators;
	table_const<string> alphabet;
	table_const<string> operation;
	table_const<string> keywords;
	
	separators.read_file("separators.txt");
	operation.read_file("operation.txt");
	alphabet.read_file("alphabet.txt");
	keywords.read_file("keywords.txt");

	//***************статические таблицы*******************//
	//проверка таблиц
	cout << "a? " << alphabet.chek("a") << endl;
	cout << "b? " << alphabet.chek("b") << endl;
	cout << "k? " << alphabet.chek("k") << endl;
	cout << ";? " << separators.chek(";") << endl;
	cout << "2? " << separators.chek("2") << endl;
	cout << "<=? " << operation.chek("<=") << endl;
	cout << "while? " << keywords.chek("while") << endl;
	cout << "int? " << keywords.chek("int") << endl;
	cout << "double? " << keywords.chek("double") << endl << endl;
	
	//добавление нового элемента и его проверка
	keywords.add("double");
	cout << "double? " << keywords.chek("double") << endl << endl;

	//поиск номера элемента по имени
	int num;
	keywords.get_num("double", num);
	cout << "num double = " << num << endl;
	keywords.get_num("main", num);
	cout << "num main = " << num << endl;
	keywords.get_num("while", num);
	cout << "num while = " << num << endl;
	keywords.get_num("int", num);
	cout << "num int = " << num << endl << endl;

	//поиск элемента по номеру
	string str;
	keywords.get_val(num, str);
	cout << num << " = " << str << endl << endl;
	

	//***************динамические таблицы*******************//
	table_var identification;
	table_var constant;

	//добавдение элементов
	constant.add("a");
	constant.add("b");
	constant.add("c");

	//повторное добавление элемента с
	bool check = constant.add("c");
	cout << "add c? " << check << endl;
	check = constant.add("n");
	cout << "add n? " << check << endl << endl;

	//проверка элемента в таблице
	check = constant.check("b");
	cout << "check b? " << check << endl;
	check = constant.check("g");
	cout << "check g? " << check << endl << endl;

	//поиск по имени
	identification.add("123");
	identification.add("321");
	identification.add("213");
	identification.add("132");
	int hash, id;
	identification.get_location("123", hash, id);
	cout << "123: hash = " << hash << " id = " << id << endl;
	identification.get_location("132", hash, id);
	cout << "132: hash = " << hash << " id = " << id << endl << endl;

	//установка значений
	identification.set_type("123",1);  //для 123 hash=50 id=0
	identification.set_type(50, 3, 1); //для 132 hash=50 id=3
	identification.set_is_init(50, 3, true);
	identification.set_is_init("123", false);
	identification.set_is_init(50, 0, true);
	lexeme test;
	identification.get_lexeme("123", test);
	cout << "test.name = " << test.name << endl;
	cout << "test.type = " << test.type << endl;
	cout << "test.is_init = " << test.is_init << endl;
	
	return 0;
}

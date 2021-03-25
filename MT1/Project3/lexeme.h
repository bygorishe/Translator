#ifndef LEXEME_H_INCLUDED
#define LEXEME_H_INCLUDED
#include <string>
#include <vector>
using namespace std;
// ����� ��� �������� ��������������� � ��������
class lexeme
{
public:
	// ��� �������������� ��� �������� ���������
	string name;
	// ���, 0 - �� ���������, 1 - int
	int type;
	// ������ ������ "���������������� ��" 
	bool is_init;
	// ����������� �� ���������
	lexeme();
	// ����������� � �������� ����� �������������� ��� �������� ���������
	lexeme(string new_name);
	// ����������
	~lexeme();
};
#endif // LEXEME_H_INCLUDED
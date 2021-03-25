#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "translator.h"
using namespace std;
int main()
{
	translator a;
	a.analyze_lexical("source.txt", "tokens.txt", "errors.txt");
	_getch();
	return 0;
}
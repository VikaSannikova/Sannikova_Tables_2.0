#pragma once
#include <iostream>
#include "List.h"
#include "HashTable.h"
#include "Word.h"
using std::string;

int readWord(char *start, char *& end, string &s, string &res);
template <typename Table>
void read_text_in_table(Table &h)
{
	string tmp, res;
	getline(cin, tmp, '\n');
	char *st = &tmp[0], *end;
	while (readWord(st, end, tmp, res) > 0)
	{
		h[res]++;
		st = end;
	}
}

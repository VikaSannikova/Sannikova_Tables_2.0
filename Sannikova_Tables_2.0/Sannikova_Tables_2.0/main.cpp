#include "HashTable.h"
#include "Word.h"
#include "ReadFunc.h"
#include "BST.h"
#include <iostream>
using std::string;
int main()
{
	cout << "enter words" << endl;
	//HashTableL<string, int, Word> h(11);
	//read_text_in_table(h);
	//h.printTable();

	queue<int> q;
	BinTree<string, int> t;
	read_text_in_table(t);
	t.printBFS();

	return 0;
}
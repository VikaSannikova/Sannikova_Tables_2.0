#pragma once
template <class Key, class Data>
class TableNode
{
public:
	Key k;
	Data d;

	TableNode() :k(), d(0) {}; //конструктор
	TableNode(Key &k1, Data &d1) : k(k1), d(d1) {}; //конструктор инициализатор 
	TableNode(Key k1, Data d1, bool f) : k(k1), d(d1) {}; 
	TableNode(Key &k1) : k(k1), d(0) {};

	Data& gd() //достать данные 
	{
		return d;
	}
	bool operator == (const TableNode &c) //оператор сравнения
	{
		return k == c.k;
	}
	bool operator < (const TableNode &c) //оператор сравнения
	{
		return k < c.k;
	}
	bool operator > (const TableNode &c) //оператор сравнения
	{
		return k > c.k;
	}
};
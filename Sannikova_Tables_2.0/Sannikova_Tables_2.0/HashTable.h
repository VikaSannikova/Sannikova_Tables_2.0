#pragma once
#include "List.h"
inline int max(int a, int b) //встроенная функция
{
	return (a > b ? a : b);
}

template <class Key, class Data, class Hash>
class HashTableL
{
private:
	int sizeTable; //размер таблицы
	List<TableNode<Key, Data>> *table; //массив списков
	int maxCollision; //максимальная коллизия в таблице

	int gHash(Key &k)  //что это
	{
		return Hash::getHash(k) % sizeTable;
	}
public:
	HashTableL(int size) : maxCollision(0) //конструктор пустой таблицы
	{
		table = new List<TableNode<Key, Data>>[size];
		sizeTable = size;
	}
	void insert(Key k, Data d) //вставка в таблицу
	{
		TableNode <Key, Data>tmp(k, d); //создаем ячейку таблицы с такими данными
		Node<TableNode<Key, Data>> *p;
		int h = gHash(k); //вычисляем хэш по ключу
		p = table[h].find(tmp); //ищем в списке под наомером h элемент с данными 
		if (p) //если есть такой элемент
			table[h].update(p, tmp); //обновляем данные 
		else table[h].push_front(tmp); //добавляем в начало списка

		maxCollision = max(table[h].getSize() - 1, maxCollision); //перерасчет максимальной коллизии
	}
	void erase(Key k) //уделение по ключу к
	{
		Data d = 0; //данные 0
		TableNode <Key, Data>tmp(k, d); //создаем элемент таблицы с такими данными
		int h = gHash(k); //вычисляем хэш
		table[h].erase(tmp); //удаляем в списке под номером h узел tmp
	}

	Data& operator [](Key k) //оператор инициализации
	{
		int h = gHash(k); //вычисляем хэш
		Data t = 0; //данные зануляем
		TableNode <Key, Data> tmp(k, t);  //создаем улез таблицы с такими данными
		Node<TableNode<Key, Data>> *p = table[h].find(tmp); //создаем указатель на этот элемент(ищем с такими данными элемент списка h)
		if (p == 0) //если не нашли такой
		{
			table[h].push_front(tmp); //то дабавляем в начало списка этот элемент
			p = table[h].find(tmp); //снова ищем
		}
		maxCollision = max(table[h].getSize() - 1, maxCollision); //перерасчет коллизии
		return p->data.gd();
	}

	int getMaxCol() { return  maxCollision; } //максимальная коллизия

	void printTable() //печать таблицы хэша
	{
		for (int i = 0; i < sizeTable; i++) //цикл до размера таблицы
		{
			while (table[i].size) //пока у нас не закончился i список
			{
				TableNode<Key, Data> t = table[i].quick_pop_front(); //достаем первый элемент из списка(в нем уменьшается size)
				cout << i << ") hash = " << Hash::getHash(t.k) << " word = " << t.k << " count = " << t.d << '\n'; //выводим на экран номер, хэш, ключ, данные 
			}
		}
		cout << "max colision = " << maxCollision << '\n'; //выводим максимальную коллизию
	}

	~HashTableL() //деструктор хэш таблицы
	{
		delete[] table;
	}
};

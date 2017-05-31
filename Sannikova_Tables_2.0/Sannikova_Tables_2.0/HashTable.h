#pragma once
#include "List.h"
inline int max(int a, int b) //���������� �������
{
	return (a > b ? a : b);
}

template <class Key, class Data, class Hash>
class HashTableL
{
private:
	int sizeTable; //������ �������
	List<TableNode<Key, Data>> *table; //������ �������
	int maxCollision; //������������ �������� � �������

	int gHash(Key &k)  //��� ���
	{
		return Hash::getHash(k) % sizeTable;
	}
public:
	HashTableL(int size) : maxCollision(0) //����������� ������ �������
	{
		table = new List<TableNode<Key, Data>>[size];
		sizeTable = size;
	}
	void insert(Key k, Data d) //������� � �������
	{
		TableNode <Key, Data>tmp(k, d); //������� ������ ������� � ������ �������
		Node<TableNode<Key, Data>> *p;
		int h = gHash(k); //��������� ��� �� �����
		p = table[h].find(tmp); //���� � ������ ��� �������� h ������� � ������� 
		if (p) //���� ���� ����� �������
			table[h].update(p, tmp); //��������� ������ 
		else table[h].push_front(tmp); //��������� � ������ ������

		maxCollision = max(table[h].getSize() - 1, maxCollision); //���������� ������������ ��������
	}
	void erase(Key k) //�������� �� ����� �
	{
		Data d = 0; //������ 0
		TableNode <Key, Data>tmp(k, d); //������� ������� ������� � ������ �������
		int h = gHash(k); //��������� ���
		table[h].erase(tmp); //������� � ������ ��� ������� h ���� tmp
	}

	Data& operator [](Key k) //�������� �������������
	{
		int h = gHash(k); //��������� ���
		Data t = 0; //������ ��������
		TableNode <Key, Data> tmp(k, t);  //������� ���� ������� � ������ �������
		Node<TableNode<Key, Data>> *p = table[h].find(tmp); //������� ��������� �� ���� �������(���� � ������ ������� ������� ������ h)
		if (p == 0) //���� �� ����� �����
		{
			table[h].push_front(tmp); //�� ��������� � ������ ������ ���� �������
			p = table[h].find(tmp); //����� ����
		}
		maxCollision = max(table[h].getSize() - 1, maxCollision); //���������� ��������
		return p->data.gd();
	}

	int getMaxCol() { return  maxCollision; } //������������ ��������

	void printTable() //������ ������� ����
	{
		for (int i = 0; i < sizeTable; i++) //���� �� ������� �������
		{
			while (table[i].size) //���� � ��� �� ���������� i ������
			{
				TableNode<Key, Data> t = table[i].quick_pop_front(); //������� ������ ������� �� ������(� ��� ����������� size)
				cout << i << ") hash = " << Hash::getHash(t.k) << " word = " << t.k << " count = " << t.d << '\n'; //������� �� ����� �����, ���, ����, ������ 
			}
		}
		cout << "max colision = " << maxCollision << '\n'; //������� ������������ ��������
	}

	~HashTableL() //���������� ��� �������
	{
		delete[] table;
	}
};

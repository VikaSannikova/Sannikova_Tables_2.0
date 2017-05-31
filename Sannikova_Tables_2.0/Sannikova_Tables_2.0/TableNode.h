#pragma once
template <class Key, class Data>
class TableNode
{
public:
	Key k;
	Data d;

	TableNode() :k(), d(0) {}; //�����������
	TableNode(Key &k1, Data &d1) : k(k1), d(d1) {}; //����������� ������������� 
	TableNode(Key k1, Data d1, bool f) : k(k1), d(d1) {}; 
	TableNode(Key &k1) : k(k1), d(0) {};

	Data& gd() //������� ������ 
	{
		return d;
	}
	bool operator == (const TableNode &c) //�������� ���������
	{
		return k == c.k;
	}
	bool operator < (const TableNode &c) //�������� ���������
	{
		return k < c.k;
	}
	bool operator > (const TableNode &c) //�������� ���������
	{
		return k > c.k;
	}
};
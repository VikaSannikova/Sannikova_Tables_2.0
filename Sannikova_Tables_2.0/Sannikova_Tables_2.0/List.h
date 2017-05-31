#pragma once
#pragma once
#include <iostream>
#include "TableNode.h"
using namespace std;

template <class Data>
struct Node
{
	Data data; //данные
	Node* next; //указатель на следующий
	Node() : next(0) {} //конструктор
	Node(const Node<Data> &n) //конструктор
	{
		data = n.data;
		next = n.next;
	}
};

template <class Data>
class List
{
protected:
	Node <Data> *head; //указатель на голову
public:
	int size; //размер списка

	List() : head(0), size(0) {}; //конструктор
	bool isEmpty() { return (head == NULL); } //проверка на пустоту
	Data quick_pop_front() //достать первый элмент из списка
	{
		Node<Data> tmp = *head; 
		Node<Data> *p = head; 
		if (head->next)
		{
			head = head->next; //если есть следующий то переносим голову
			delete p;
		}
		else
		{
			delete head; //если нет следующего то просто пустой список
			head = 0;
		}
		size--; //уменьшаем размер
		return tmp.data; //возвращем данные из прдварительно сохраненной головы
	}
	void push_front(Data obj) //добавление в начала первого элемента
	{
		Node<Data> *newNode = new Node<Data>; //моздаем новый элемент
		newNode->data = obj; //заносим в него данные 
		newNode->next = head; //следующим для нового элемента станет голова
		head = newNode; //голово станет новый
		size++; //увеличиваем размер
	}
	Node<Data>* find(Data &obj) //поиск в списке
	{
		Node <Data> *tmp = head; //новый узел - голова
		while (tmp)
		{
			if (tmp->data == obj) //если данные совпали
				return tmp;       //то возвращаем этот узел
			tmp = tmp->next; //переходим к следующему узлу
		}
		delete tmp; //удаляем этот узел
		return 0;
	}
	void update(Node <Data> *p, Data &n) //обновление данных в конкретном узле
	{
		p->data = n;
	}
	void erase(Data &obj) //удаление узда с заданными данными
	{
		Node <Data> *tmp = head, *pre = 0;
		while (tmp)
		{
			if (tmp->data == obj)  //если данные совпали
			{
				if (pre) //если предыдущий сущетвует
					pre->next = tmp->next; //следующим за предыдущим станет следующий за текущим
				else head = tmp->next; //если нет предыдущего, то головой станет следующий

				delete tmp; //удалям узел

				return;
			}
			pre = tmp; //сдвиг по узлам
			tmp = tmp->next;
		}
	}
	int getSize() //элемент списка
	{
		return size;
	}
	void reverce() //переворачивание списка
	{
		Node<Data> *tmp = 0;
		Node<Data> *next = 0;
		if (head)
			next = head->next;
		while (next != 0)
		{
			head->next = tmp;
			tmp = head;
			head = next;
			next = head->next;
		}
		head->next = tmp;
	}
	~List() //деструктор
	{
		Node <Data> *tmp;
		while (!isEmpty())
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}
};

#pragma once
#include <queue>
#include "TableNode.h"
#define node NodeTreeAVL<TableNode<Key, Data>>
#define cont TableNode<Key, Data>

template <class Data>
struct NodeTreeAVL
{
	Data data; //данные 
	NodeTreeAVL* left; //указатель на левый
	NodeTreeAVL* right; //указатель на правый
	int height;

	NodeTreeAVL() : left(0), right(0), height(0) {} //конструктор
	NodeTreeAVL(const Data &d) //конструктор
	{
		data = d;
		left = 0;
		right = 0;
		height = 1;
	}
	NodeTreeAVL(const NodeTreeAVL<Data> &n) //конструктор копирования
	{
		data = n.data;
		left = n.left;
		right = n.right;
		height = n.height;
	}
};

template <class Key, class Data>
class AVL
{
private:
	int size; //размер таблицы
	NodeTreeAVL<TableNode<Key, Data>> *root; //указатель на корень
	inline void insNodeToLeft(node *ins, node *was) //что это
	{

	}
	inline void insNodeToRight(node *ins, node *was) //что это
	{

	}
	inline node* getLeftNode(node *n) //достать левый узел
	{
		if (n)
			return n->left;
	}
	inline node* getRightNode(node *n) //достать правый узел
	{
		if (n)
			return n->right;
	}
	void insertAfterTmp(node *tmp, node *ins)//начиная с узла tmp вставь узел ins
	{
		node *pred; //создаем узел дерева
		int i; //индекс поворота
		while (tmp) //пока узел есть
		{
			pred = tmp; //передыдущий становится тмп
			if (ins->data < tmp->data) //если входные данные меньше данных тмп
			{
				i = 0; //индикатор влево
				tmp = tmp->left; //переносим узел тмп
			}
			else if (ins->data > tmp->data) //если входные данные больше
			{
				i = 1; //индикатор вправо
				tmp = tmp->right; //переносим узел тмп
			}
			else
			{
				tmp->data = ins->data; //если обновляем данные
				return;
			}
		}
		if (i == 0)	pred->left = ins; //если влево то левым потомком становится входной узел
		else pred->right = ins; //если нет то правым
		size++; //увеличиваем данные
	}
public:
	AVL() : size(0), root(0) {};
	int length()
	{
		return size;
	}
	void insert(Key k, Data d) //обертка для вставки
	{
		if (!root) //если дерево пустое
		{
			root = new node(cont(k, d)); //то будет один узел один
			size++;
			return;
		}
		node *tmp = new node(cont(k, d)); //создаем узел
		insertAfterTmp(root, tmp); //вставляем tmp
	}
	void erase(Key k) //удаление по ключу
	{
		Data t(0); //обнуляем данные
		cont el(k, t); //создаем такой узел
		node *pred = 0, *tmp = root; //создаем свободный узел и указатель на корень
		int i; //индикатор
		while (tmp) //пока сществует тмп
		{
			if (el < tmp->data) //если данные элемента меньше то сдвигаемся вправо
			{
				i = 0;
				pred = tmp; //передвигаем пред
				tmp = tmp->left; //передвигаем тмп
			}
			else if (el > tmp->data)//если больше
			{
				i = 1;
				pred = tmp; //передвигаем пред
				tmp = tmp->right;//передвигаем тмп
			}
			else//если совпали
			{
				size--; //уменьшаем длину
				if (pred) //есть предыдущий
				{
					if (i == 0) //если влево
					{
						if (tmp->left)//если у тмп есть левый узел
							insertAfterTmp(pred, tmp->left); //вставляем после придка левый узел
						if (tmp->right)
							insertAfterTmp(pred, tmp->right);//вставляем правый узел
						pred->left = 0;
					}
					else
					{
						if (tmp->left)
							insertAfterTmp(pred, tmp->left);//вставляем левый узел
						if (tmp->right)
							insertAfterTmp(pred, tmp->right);//вставляем правый узел
						pred->right = 0;
					}

					delete tmp;
					return;
				}
				delete root;//пустое дерево
				root = 0;
				return;
			}
		}
	}
	Data& operator [](Key k) //перегрузка инициализации
	{
		Data t(0);
		TableNode<Key, Data> el(k, t); //создаем элемент с такими данными
		NodeTreeAVL<TableNode<Key, Data>>*pred = 0, *tmp = root; //узлы дерева
		int i;
		while (tmp) //пока у нас есть узел
		{
			pred = tmp; //передвигаем пред
			if (el < tmp->data) //если данныме меньше
			{
				i = 0; //пот индикатор ухода влево
				tmp = tmp->left; //передвигаем тмп
			}
			else if (el > tmp->data) //если данные больше 
			{
				i = 1; //индикатор вправо
				tmp = tmp->right; //передвигаем тмп вправо
			}
			else
			{
				return tmp->data.gd();//достаем данные из узла
			}
		}
		size++; //увеличиваем размер сдерева
		tmp = new NodeTreeAVL<TableNode<Key, Data>>(); //тмп пустой новый узел
		tmp->data = el; //устанавливаем в данные элемента новые данные
		if (root == 0) //если у нас пустое дерево
			root = tmp; //то сздаем новое дерево из одного узла
		else
		{
			if (i == 0)	pred->left = tmp; //если 
			else pred->right = tmp;
		}
		return tmp->data.gd();
	}
	NodeTreeAVL<TableNode<Key, Data>>*find(Key k) //поиск элемента по ключу

	{
		Data t(0);
		TableNode<Key, Data> el(k, t); //создаем элемент с такими данными
		NodeTreeAVL<TableNode<Key, Data>> *tmp = root; //указатель на корень
		while (tmp) //пока существует элемент
		{
			if (el < tmp->data) //если данные элемента меньше данных узла
				tmp = tmp->left; ///спускаемся в левого сына
			else if (el > tmp->data) //если данные больше 
				tmp = tmp->right; //то спускаемся в правого сына
			else
				return tmp; //возвращаем узел
		}
		return 0; //ничего не нашли
	}


	void printBFS() //печать дерева
	{
		queue<NodeTreeAVL<TableNode<Key, Data>>*> q; //очередь из листов
		if (root) //если существует корень
			q.push(root); //то добавляем корень
		while (!q.empty()) //пока очередь не пуста
		{
			NodeTreeAVL<TableNode<Key, Data>> *tmp = q.front(); //первый элемент в очереди
			cout << tmp->data.k << ' ' << tmp->data.d << '\n'; //вывести ключ элемента и данные
			if (tmp->left) //если есть левый сын
				q.push(tmp->left); //то поместить в очередь его
			if (tmp->right)
				q.push(tmp->right);//пометить в очередь его
			q.pop(); //вывести из очереди первый элемент
		}
	}
};
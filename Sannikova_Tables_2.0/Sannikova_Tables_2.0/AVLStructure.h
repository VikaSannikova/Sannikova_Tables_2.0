#pragma once
struct AVLNode // структура для представления узлов дерева
{
	int key;   //ключ
	unsigned char height; //высота воддерева в данной вершине
	AVLNode* left; //указатель на левый
	AVLNode* right; //указатель на правый
	AVLNode(int k) //создает дерево из 1 вершины
	{
		key = k;
		left = right = 0;
		height = 1;
	}
};

unsigned char height(AVLNode* p) //вычисляет высоту, работает в для 0 вершин тоже
{
	return p ? p->height : 0; //вершина р есть возвращаем высоту. вершины нет 0
}

int bfactor(AVLNode* p) //расчитывает баланс
{
	return height(p->right) - height(p->left); //разница между высотами левого и правого поддеревьев
}

void fixheight(AVLNode* p) //расчет настоящей высоты в узле
{
	unsigned char hl = height(p->left); //высота левого поддерева
	unsigned char hr = height(p->right); //высота правого поддерева
	p->height = (hl>hr ? hl : hr) + 1; //высота будет равна максимальному значению + 1
}


AVLNode* rotateright(AVLNode* p) // правый поворот вокруг p
{
	AVLNode* q = p->left; //это левый потомок вершины р
	p->left = q->right;  //левым потомком р станет правый потомок q
	q->right = p; //правым потом q сталет p
	fixheight(p); //устанавливаем новую высоту для р
	fixheight(q); //устанавливаем новую высоту для q
	return q; //q теперь корень, возвращаем корень
}

AVLNode* rotateleft(AVLNode* q) // левый поворот вокруг q
{
	AVLNode* p = q->right; //p это правый потомок q
	q->right = p->left; //правыым потомком q становится левый потомок р
	p->left = q; //левым потомком p становится q
	fixheight(q); //корректировка высоты
	fixheight(p); //корректировка высоты
	return p;
}

AVLNode* balance(AVLNode* p) // балансировка узла p
{
	fixheight(p); //расчет высоты для p
	if (bfactor(p) == 2) //если перевес справва на 2
	{
		if (bfactor(p->right) < 0) //если перевес правого потомка меньше 0
			p->right = rotateright(p->right);  //то для правого потомка надо выполнить правый поворот
		return rotateleft(p); //делаем левый вопрот для корня
	}
	if (bfactor(p) == -2) //если перевес слева на 2
	{
		if (bfactor(p->left) > 0) //если перевес левого потомка больше 0
			p->left = rotateleft(p->left); //то для левого потомка надо выполнить левый поворот
		return rotateright(p); //делает правый поворот для корня
	}
	return p; // балансировка уже не нужна
}

AVLNode* insert(AVLNode* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new AVLNode(k); //если дерево пустое то создаем дерево из 1 вершины
	if (k<p->key)  //если ключ вставляемой вершины меньше ключа р
		p->left = insert(p->left, k); //то рекурсивно вставляем для левого поддерева наш узел
	else
		p->right = insert(p->right, k); //в противном случает рекурсивно вставляем в правое поддерево
	return balance(p); //выполняем балансировку корня
}

AVLNode* findmin(AVLNode* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p; //если левое поддеревое есть то рекурсивно ищем для него минимум иначе возвращаем этот узел
}

AVLNode* removemin(AVLNode* p) // изъятие узла с минимальным ключом из дерева p
{
	if (p->left == 0) //если слева у узла ничего нет, то позвращаем правое поддерево
		return p->right;
	p->left = removemin(p->left); //для левого поддерева узла вызываем рекурсию с поиском минимума
	return balance(p); //возвращаем сбалансированное дерево
}

AVLNode* remove(AVLNode* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0; //если дерево пустое
	if (k < p->key) //если ключ меньше ключа
		p->left = remove(p->left, k); //то для левого поддерева вызываем изъятие ключа
	else
		if (k > p->key) //если ключ больше ключа р
			p->right = remove(p->right, k); //то вызываем изъятие для правого поддерева
		else //  k == p->key 
		{
			AVLNode* q = p->left; //это праавое поддерева корня
			AVLNode* r = p->right; //это левое поддерево корня
			delete p; //удаляем корень
			if (!r)
				return q; //если правое поддерево пустое то возвращаем левое поддерево
			AVLNode* min = findmin(r); //ищем минимум в правом поддереве
			min->right = removemin(r); //правым потомком минимума станомится правое поддерево без минимума
			min->left = q; //левым потомком минимума становится правое поддерево 
			return balance(min); //делаем балансировку для минимума( это корень нашего поддерева)
		}
	return balance(p); //балансируем дерево р на всякий
}


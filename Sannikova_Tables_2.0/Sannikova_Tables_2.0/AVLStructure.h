#pragma once
struct AVLNode // ��������� ��� ������������� ����� ������
{
	int key;   //����
	unsigned char height; //������ ��������� � ������ �������
	AVLNode* left; //��������� �� �����
	AVLNode* right; //��������� �� ������
	AVLNode(int k) //������� ������ �� 1 �������
	{
		key = k;
		left = right = 0;
		height = 1;
	}
};

unsigned char height(AVLNode* p) //��������� ������, �������� � ��� 0 ������ ����
{
	return p ? p->height : 0; //������� � ���� ���������� ������. ������� ��� 0
}

int bfactor(AVLNode* p) //����������� ������
{
	return height(p->right) - height(p->left); //������� ����� �������� ������ � ������� �����������
}

void fixheight(AVLNode* p) //������ ��������� ������ � ����
{
	unsigned char hl = height(p->left); //������ ������ ���������
	unsigned char hr = height(p->right); //������ ������� ���������
	p->height = (hl>hr ? hl : hr) + 1; //������ ����� ����� ������������� �������� + 1
}


AVLNode* rotateright(AVLNode* p) // ������ ������� ������ p
{
	AVLNode* q = p->left; //��� ����� ������� ������� �
	p->left = q->right;  //����� �������� � ������ ������ ������� q
	q->right = p; //������ ����� q ������ p
	fixheight(p); //������������� ����� ������ ��� �
	fixheight(q); //������������� ����� ������ ��� q
	return q; //q ������ ������, ���������� ������
}

AVLNode* rotateleft(AVLNode* q) // ����� ������� ������ q
{
	AVLNode* p = q->right; //p ��� ������ ������� q
	q->right = p->left; //������� �������� q ���������� ����� ������� �
	p->left = q; //����� �������� p ���������� q
	fixheight(q); //������������� ������
	fixheight(p); //������������� ������
	return p;
}

AVLNode* balance(AVLNode* p) // ������������ ���� p
{
	fixheight(p); //������ ������ ��� p
	if (bfactor(p) == 2) //���� ������� ������� �� 2
	{
		if (bfactor(p->right) < 0) //���� ������� ������� ������� ������ 0
			p->right = rotateright(p->right);  //�� ��� ������� ������� ���� ��������� ������ �������
		return rotateleft(p); //������ ����� ������ ��� �����
	}
	if (bfactor(p) == -2) //���� ������� ����� �� 2
	{
		if (bfactor(p->left) > 0) //���� ������� ������ ������� ������ 0
			p->left = rotateleft(p->left); //�� ��� ������ ������� ���� ��������� ����� �������
		return rotateright(p); //������ ������ ������� ��� �����
	}
	return p; // ������������ ��� �� �����
}

AVLNode* insert(AVLNode* p, int k) // ������� ����� k � ������ � ������ p
{
	if (!p) return new AVLNode(k); //���� ������ ������ �� ������� ������ �� 1 �������
	if (k<p->key)  //���� ���� ����������� ������� ������ ����� �
		p->left = insert(p->left, k); //�� ���������� ��������� ��� ������ ��������� ��� ����
	else
		p->right = insert(p->right, k); //� ��������� ������� ���������� ��������� � ������ ���������
	return balance(p); //��������� ������������ �����
}

AVLNode* findmin(AVLNode* p) // ����� ���� � ����������� ������ � ������ p 
{
	return p->left ? findmin(p->left) : p; //���� ����� ���������� ���� �� ���������� ���� ��� ���� ������� ����� ���������� ���� ����
}

AVLNode* removemin(AVLNode* p) // ������� ���� � ����������� ������ �� ������ p
{
	if (p->left == 0) //���� ����� � ���� ������ ���, �� ���������� ������ ���������
		return p->right;
	p->left = removemin(p->left); //��� ������ ��������� ���� �������� �������� � ������� ��������
	return balance(p); //���������� ���������������� ������
}

AVLNode* remove(AVLNode* p, int k) // �������� ����� k �� ������ p
{
	if (!p) return 0; //���� ������ ������
	if (k < p->key) //���� ���� ������ �����
		p->left = remove(p->left, k); //�� ��� ������ ��������� �������� ������� �����
	else
		if (k > p->key) //���� ���� ������ ����� �
			p->right = remove(p->right, k); //�� �������� ������� ��� ������� ���������
		else //  k == p->key 
		{
			AVLNode* q = p->left; //��� ������� ��������� �����
			AVLNode* r = p->right; //��� ����� ��������� �����
			delete p; //������� ������
			if (!r)
				return q; //���� ������ ��������� ������ �� ���������� ����� ���������
			AVLNode* min = findmin(r); //���� ������� � ������ ���������
			min->right = removemin(r); //������ �������� �������� ���������� ������ ��������� ��� ��������
			min->left = q; //����� �������� �������� ���������� ������ ��������� 
			return balance(min); //������ ������������ ��� ��������( ��� ������ ������ ���������)
		}
	return balance(p); //����������� ������ � �� ������
}


/*Đề 10: 
Cài đặt cây nhị tìm kiếm phân dùng danh sách liên kết.
1. Viết hàm thêm một node vào cây nhị phân tìm kiếm.
2. Viết hàm xóa một node khỏi cây nhị phần tìm kiếm.
3. Viết hàm in ra đường đi của cây theo NLR, LNR, LRN.
*/
#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* pLeft;
	struct node* pRight;
};
typedef struct node NODE;
typedef NODE* TREE;

void KhoiTao(TREE& t)
{
	t = NULL;
}

void ThemNodeVaoCay(TREE& t, int x) {
	if (t == NULL) {
		NODE* p = new NODE;
		p->data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p;
	}
	else {
		if (t->data > x) {
			ThemNodeVaoCay(t->pLeft, x);
		}
		else if (t->data < x) {
			ThemNodeVaoCay(t->pRight, x);
		}
	}
}
void NodeTheMang(TREE& X, TREE& Y) {
	if (Y->pLeft != NULL)
	{
		NodeTheMang(X, Y->pLeft);
	}
	else
	{
		X->data = Y->data;
		X = Y;
		Y = Y->pRight;
	}
}
void XoaNode(TREE& t, int data)
{

	if (t == NULL)
	{
		return;
	}
	else
	{
		if (data < t->data)
		{
			XoaNode(t->pLeft, data);
		}
		else if (data > t->data)
		{
			XoaNode(t->pRight, data);
		}
		else
		{
			NODE* X = t;
			if (t->pLeft == NULL)
			{
				t = t->pRight;
			}
			else if (t->pRight == NULL)
			{
				t = t->pLeft;
			}
			else
			{
				NodeTheMang(X, t->pRight);
			}
			delete X;
		}
	}
}

void NLR(TREE t) {
	if (t != NULL)
	{
		printf(" %d ", t->data);
		NLR(t->pLeft);
		NLR(t->pRight);
	}
}
void LNR(TREE t) {
	if (t != NULL)
	{
		LNR(t->pLeft);
		printf(" %d ", t->data);
		LNR(t->pRight);
	}
}
void LRN(TREE t) {
	if (t != NULL)
	{
		LRN(t->pLeft);
		LRN(t->pRight);
		printf(" %d ", t->data);
	}
}

int main() {
	TREE t;
	KhoiTao(t);
	ThemNodeVaoCay(t, 10);
	ThemNodeVaoCay(t, 1);
	ThemNodeVaoCay(t, 3);
	ThemNodeVaoCay(t, 7);
	ThemNodeVaoCay(t, 5);
	ThemNodeVaoCay(t, 9);
	ThemNodeVaoCay(t, 4);
	ThemNodeVaoCay(t, 2);

	XoaNode(t, 3);
	XoaNode(t, 7);

	printf("\nDuyet NLR\n");
	NLR(t);
	printf("\nDuyet LNR\n");
	LNR(t);
	printf("\nDuyet LRN\n");
	LRN(t);
}
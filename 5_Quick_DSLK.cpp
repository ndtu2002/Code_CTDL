/*Cài đặt danh sách liên kết kép cho dãy sinh viên, viết hàm thêm vào đầu, xóa phần tử cuối, tìm một phần tử sinh viên trong danh sách liên kết theo MSSV.
Cài đặt thuật toán Quick Sort trên mối liên kết của danh sách để xếp tăng danh sách theo điểm trung bình của 5 môn.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SinhVien {
	char ten[20];
	char ms[10];
	float diem[5];
};
void nhap(SinhVien& sv) {
	printf("Nhap ten: \n");
	fflush(stdin);
	fgets(sv.ten, 20, stdin);
	printf("Nhap ma so: \n");
	fgets(sv.ms, 10, stdin);
	for (int i = 0; i < 5; i++) {
		printf("Nhap diem %d \n", i + 1);
		scanf_s("%f", &sv.diem[i]);
	}
	getchar();
}
void xuat(SinhVien sv) {
	printf("\nHo va ten: \n");
	printf("%s", sv.ten);
	printf("Ma so: \n");
	printf("%s", sv.ms);
	for (int i = 0; i < 5; i++) {
		printf("%f ", sv.diem[i]);
	}
}
SinhVien TaoSV() {
	SinhVien sv;
	nhap(sv);
	return sv;
}

typedef struct node {
	SinhVien data;
	node* pre;
	node* next;
};
typedef struct list {
	node* last;
	node* first;
};
void init(list& l) {
	l.first = l.last = NULL;
}
node* getnode(SinhVien x) {
	node* p = new node();
	if (p != NULL) {
		p->data = x;
		p->next = p->pre = NULL;
	}
	return p;
}
void addfirst(list& l, SinhVien x) {
	node* p = getnode(x);
	if (p != NULL) {
		if (l.first == NULL) { l.first = l.last = p; }
		else {
			p->next = l.first;
			l.first->pre = p;
			l.first = p;
		}
	}
}

void addlast(list& l, SinhVien x) {
	node* p = getnode(x);
	if (p != NULL) {
		if (l.first == NULL)
		{
			l.first = l.last = p;
		}
		else {
			p->pre = l.last;
			l.last->next = p;
			l.last = p;
		}
	}
}
void AddLast(list& l, node* new_ele) {
	if (l.first == NULL) {
		l.first = new_ele;
		l.last = new_ele;
	}
	else {
		l.last->next = new_ele;
		new_ele->pre = l.last;
		l.last = new_ele;
	}
}
void xoadau(list& l) {
	if (l.first == NULL) {
		return;
	}
	node* temp = l.first;
	l.first = l.first->next;
	if (l.first == NULL) {
		l.last = NULL;
	}
	else {
		l.first->pre = NULL;
	}
	delete temp;
}
void xoacuoi(list& l) {
	if (l.last == NULL) {
		return;
	}
	node* temp = l.last;
	l.last = l.last->pre;
	if (l.last == NULL) {
		l.first = NULL;
	}
	else {
		l.last->next = NULL;
	}
	delete temp;
}
void output(list l) {
	node* p = l.first;
	while (p != NULL) {
		xuat(p->data);
		p = p->next;
	}
}
void checkMSSV(list l) {
	char mssv[10];
	node* p = l.first;
	printf("Nhap ma so can tim: ");
	fgets(mssv, 10, stdin);
	int flag = 0;
	while (p != NULL) {
		if (strcmp(mssv, p->data.ms) == 0) {
			xuat(p->data);
			flag = 1;
		}
		p = p->next;
	}
	if (flag == 0)
		printf("Khong thay");
}
void DListAppend(list& l, list& lx) {
	if (lx.first != NULL) {
		if (l.first == NULL)
			l = lx;
		else
			l.last->next = lx.first;
	}
	init(lx);
}

float dtb(SinhVien x) {
	float dtb = (x.diem[0] + x.diem[1] + x.diem[2] + x.diem[3] + x.diem[4]) / 5;
	return dtb;
}
void QuickSort(list& l) {
	if (l.first == NULL || l.first == l.last) {
		return;
	}
	node* p, * X;
	list l1, l2;
	init(l1);
	init(l2);
	X = l.first;
	l.first = X->next;
	while (l.first != NULL) {
		p = l.first;
		l.first = p->next;
		p->next = NULL;
		if (dtb(p->data) <= dtb(X->data)) {
			AddLast(l1, p);
		}
		else {
			AddLast(l2, p);
		}
	}
	QuickSort(l1);
	QuickSort(l2);
	if (l1.first != NULL) {
		l.first = l1.first;
		l1.last->next = X;
		X->pre = l1.last;
	}
	else {
		l.first = X;
	}
	X->next = l2.first;
	if (l2.first != NULL) {
		l.last = l2.last;
		l2.first->pre = X;
	}
	else {
		l.last = X;
	}
}

int main() {
	list l;
	init(l);
	SinhVien sv1, sv2, sv3;
	sv1 = TaoSV();
	sv2 = TaoSV();
	sv3 = TaoSV();
	addfirst(l, sv1);
	addfirst(l, sv2);
	addfirst(l, sv3);
	checkMSSV(l);
	output(l);
}
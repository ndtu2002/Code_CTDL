#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*=====================CAI DAT STRUCT SV=====================*/
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

/*=====================CAI DAT DSLK=====================*/
typedef struct node {
	SinhVien data;
	node* pre;
	node* next;
} node;
struct list {
	node* first;
	node* last;
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
	node* newnode  = getnode(x);
	while (newnode != NULL) {
		if (l.first == NULL) {
			l.first = l.last = newnode;
		}
		else {
			newnode->next = l.first;
			l.first->pre = newnode;
			l.first = newnode;
		}
	}
}
void addlast(list& l, SinhVien x) {
	node* newnode = getnode(x);
	if (newnode != NULL) {
		if (l.first == NULL) {
			l.first = l.last = newnode;
		}
		else {
			l.last->next = newnode;
			newnode->pre = l.last;
			l.last = newnode;
		}
	}
}
void output(list l) {
	node* p = l.first;
	while (p != NULL) {
		xuat(p->data);
		p = p->next;
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
/*=====================CAI DAT MERGE SORT=====================*/
float dtb(SinhVien& x) {
	float dtb = (x.diem[0] + x.diem[1] + x.diem[2] + x.diem[3] + x.diem[4]) / 5;
	return dtb;
}
void copy(list x, list& y) {
	if (x.first == NULL)
		init(y);
	else {
		node* p = x.first;
		while (p != NULL) {
			addlast(y, p->data);
			p = p->next;
		}
	}
}
void insert(list& l, SinhVien x) {
	node* newnode = getnode(x);
	if (newnode != NULL) {
		if (l.first == NULL) {
			l.first = l.last = newnode;
		}
		else {
			if (dtb(x) < dtb(l.first->data)) {
				addfirst(l, x);
			}
			else {
				if (dtb(x) > dtb(l.last->data)) {
					addlast(l, x);
				}
				else
				{
					node* p = l.first;
					while (p != NULL) {
						if (dtb(x) < dtb(p->data)) {
							newnode->next = p;
							newnode->pre = p->pre;
							p->pre->next = newnode;
							p->pre = newnode;
							break;
						}
						p = p->next;
					}
				}
			}
		}
	}
}
void insertlist(list x, list y, list& z) {
	if (y.first == NULL)
		copy(x, z);
	else
	{
		node* p = y.first;
		while (p != NULL) {
			insert(x, p->data);
			p = p->next;
		}
		copy(x, z);
	}
}
void merge(list& l, int n, int& hso) {
	double k = pow(2, hso);
	if (k <= n) {
		int i = 0, b = 1;
		list x, y, z;
		node* p = l.first;
		init(x); init(y); init(z);
		while (i < n) {
			double a = 0;
			while ((a != k) && (i < n)) {
				i++; a++;
				if (b % 2 == 0) {
					addlast(y, p->data);
				}
				else {
					addlast(x, p->data);
				}
				p = p->next;
			}
			if (b % 2 == 0) {
				insertlist(x, y, z);
				init(x); init(y);
			} b++;
		}
		if (b % 2 == 0) {
			insertlist(x, y, z);
			init(x); init(y);
		}
		init(l);
		copy(z, l);
		hso++;
		merge(l, n, hso);
	}
}
int main() {
	list l;
	init(l);
	SinhVien sv1, sv2, sv3;
	int hso = 0;
	sv1 = TaoSV();
	sv2 = TaoSV();
	sv3 = TaoSV();
	addlast(l, sv1);
	addlast(l, sv2);
	addlast(l, sv3);
	merge(l, 3, hso);
	output(l);
}

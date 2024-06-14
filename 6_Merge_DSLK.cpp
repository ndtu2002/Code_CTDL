#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct node
{
	int data;
	node* next;
	node* pre;
};

struct list {
	node* first;
	node* last;
};

void init(list& l) {
	l.first = l.last = NULL;
}

node* getnode(int x) {
	node* p = new node();
	if (p != NULL) {
		p->data = x;
		p->next = p->pre = NULL;
	}
	return p;
}

void addfirst(list& l, int x) {
	node* newnode = getnode(x);
	if (newnode != NULL) {
		if (l.first == NULL) {
			l.first = l.last = newnode;
		}
		else
		{
			newnode->next = l.first;
			l.first->pre = newnode;
			l.first = newnode;
		}
	}
}
void addlast(list& l, int x) {
	node* newnode = getnode(x);
	if (newnode != NULL) {
		if (l.first == NULL) {
			l.first = l.last = newnode;
		}
		else
		{
			l.last->next = newnode;
			newnode->pre = l.last;
			l.last = newnode;
		}
	}
}
void xoadau(list& l) {
	if (l.first == NULL) {
		return; // List is empty, nothing to delete
	}

	node* temp = l.first;
	l.first = l.first->next;

	// If there was only one element, update last as well
	if (l.first == NULL) {
		l.last = NULL;
	}
	else {
		l.first->pre = NULL;
	}

	delete temp;
}

// Function to delete the last element
void xoacuoi(list& l) {
	if (l.last == NULL) {
		return; // List is empty, nothing to delete
	}

	node* temp = l.last;
	l.last = l.last->pre;

	// If there was only one element, update first as well
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
		printf("%d ", p->data);
		p = p->next;
	}
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
void insert(list& l, int x) {
	node* newnode = getnode(x);
	if (newnode != NULL) {
		if (l.first == NULL) {
			l.first = l.last = newnode;
		}
		else {
			if (x < l.first->data) {
				addfirst(l, x);
			}
			else {
				if (x > l.last->data) {
					addlast(l, x);
				}
				else
				{
					node* p = l.first;
					while (p != NULL) {
						if (x < p->data) {
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
	int n, hso = 0;
	list l;
	init(l);
	addlast(l, 1);
	addlast(l, 9);
	addlast(l, 4);
	addlast(l, 2);
	merge(l, 4, hso);
	output(l);

}
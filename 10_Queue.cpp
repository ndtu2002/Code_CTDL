#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
    char data;
    struct node* next;
}; typedef struct node NODE;
struct queue {
    NODE* head;
    NODE* tail;
}; typedef struct queue QUEUE;

void initQueue(QUEUE& q) {
    q.head = NULL;
    q.tail = NULL;
}

NODE* createNode(char x) {
    NODE* p = new NODE;
    if (p == NULL) {
        printf("Khong du bo nho");
    }
    p->data = x;
    p->next = NULL;
    return p;
}
bool isEmpty(QUEUE q) {
    if (q.head == NULL) return true;
    return false;
}
void Push(QUEUE& q, char x) {
    NODE* p = createNode(x);
    if (isEmpty(q)) {
        q.head = q.tail = p;
    }
    else {
        q.tail->next = p;
        q.tail = p;
    }
}
char Pop(QUEUE& q) {
    if (isEmpty(q)) {
        printf("Queue rong!");
    }
    NODE* temp = q.head;
    char x = temp->data;
    q.head = q.head->next;
    if (q.head == NULL) q.tail = NULL;

    delete temp;
    return x;
}
QUEUE reverseQueue(QUEUE q) {
    if (q.head == NULL || q.head->next == NULL) {
        printf("Queue rong!");
    }

    NODE* prev = NULL;
    NODE* curr = q.head;
    NODE* n;

    while (curr != NULL) {
        n = curr->next;
        curr->next = prev;
        prev = curr;
        curr = n;
    }

    q.tail = q.head;
    q.head = prev;

    QUEUE x = q;

    return x;
}

bool check(char s[]) {
    QUEUE q;
    initQueue(q);
    for (int i = 0; i < strlen(s); i++) {
        Push(q, s[i]);
    }
    QUEUE x = reverseQueue(q);
    bool ok = true;
    while (!isEmpty(q)) {
        char c1 = Pop(q);
        char c2 = Pop(x);
        if (c1 != c2)
        {
            ok = false;
            break;
        }
    }

    return ok;
}
void isPld(char s[]) {
    bool ok = check(s);
    if (ok) printf("TRUE\n");
    else printf("FALSE\n");

}
void printQueue(QUEUE queue) {
    NODE* curr = queue.head;
    while (curr != NULL) {
        printf("%c ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}
int main() {
    QUEUE q;
    initQueue(q);
    char s1[] = "radar";
    char s2[] = "hello";
    char s3[] = "madam";
    isPld(s1);
    isPld(s2);
    isPld(s3);

    return 0;
}

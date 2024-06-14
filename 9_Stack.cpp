/*Đề 8: Cài đặt :
1. Cài đặt stack dùng danh sách liên kết với phần dữ liệu là kí tự.
2. Viết hàm kiểm tra xem một chuỗi đầu vào có phải là một dãy ngoặc đúng(parentheses, brackets và braces) hay không bằng cách sử dụng stack.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
    char data;
    struct node* next;
};

typedef struct node NODE;
typedef struct node* PNODE;

struct stack {
    PNODE top;
};

typedef struct stack STACK;


void InitStack(STACK& s) {
    s.top = NULL;
}

bool IsEmptyStack(STACK s) {
    if (s.top == NULL) return 1;
    return 0;
}

void Push(STACK& s, char x) {
    PNODE p = new NODE;
    if (p == NULL) {
        printf("Khong du bo nho!\n");
        return;
    }

    p->data = x;
    p->next = s.top;
    s.top = p;
}

char Pop(STACK& s) {
    if (IsEmptyStack(s)) {
        printf("Stack rong!\n");
        return '\0'; // Or any special value to indicate error
    }

    PNODE temp = s.top;
    char x = temp->data;
    s.top = s.top->next;
    delete temp;
    return x;
}
char Top(STACK s) {
    return s.top->data;
}
bool check(char s[]) {
    bool ok = false;
    STACK stk;
    InitStack(stk);
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '}' && !IsEmptyStack(stk) && Top(stk) == '{') Pop(stk);
        else if (s[i] == ']' && !IsEmptyStack(stk) && Top(stk) == '[') Pop(stk);
        else if (s[i] == ')' && !IsEmptyStack(stk) && Top(stk) == '(') Pop(stk);
        else Push(stk, s[i]);
    }
    if (IsEmptyStack(stk)) ok = true;

    return ok;
}
void kiemtrangoac(char s[]) {
    bool ok = check(s);
    if (ok) printf("TRUE");
    else printf("FALSE");
}

int main() {
    char string1[] = "{[()]}";
    char string2[] = "(()){{}";
    char string3[] = "))))";
    char string4[] = "({[()]})";
    kiemtrangoac(string3);

    return 0;
}
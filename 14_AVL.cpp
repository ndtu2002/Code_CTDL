/*Cài đặt cây nhị phân AVL bằng danh sách liên kết
Viết hàm tạo ngẫu nhiên cây AVL từ một mãng chữ số.
Viết hàm thêm một node có giá trị ngẫu nhiên vào AVL.
Viết hàm cân bằng lại cây AVL.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LH -1 //cây con trái cao hơn
#define EH -0 //Hai cây con bằng nhau
#define RH 1  //cây con phải cao hơn
typedef struct tagAVLNode
{
    char balFactor; //chi so can bang
    int key;
    struct tagAVLNode* pLeft;
    struct tagAVLNode* pRight;
}AVLNode;
typedef AVLNode* AVLTree;
//quay don LL
void rotateLL(AVLTree& T) {
    AVLNode* T1 = T->pLeft;
    T->pLeft = T1->pRight;
    T1->pRight = T;
    switch (T1->balFactor) {
    case LH:
        T->balFactor = EH;
        T1->balFactor = EH;
        break;
    case EH:
        T->balFactor = LH;
        T1->balFactor = RH;
        break;
    }
    T = T1;
}

//quay don RR
void rotateRR(AVLTree& T) {
    AVLNode* T1 = T->pRight;
    T->pRight = T1->pLeft;
    T1->pLeft = T;
    switch (T1->balFactor) {
    case RH:
        T->balFactor = EH;
        T1->balFactor = EH;
        break;
    case EH:
        T->balFactor = RH;
        T1->balFactor = LH;
        break;
    }
    T = T1;
}

//quay kep LR
void rotateLR(AVLTree& T) {
    AVLNode* T1 = T->pLeft;
    AVLNode* T2 = T1->pRight;
    T->pLeft = T2->pRight;
    T2->pRight = T;
    T1->pRight = T2->pLeft;
    T2->pLeft = T1;
    switch (T2->balFactor) {
    case LH:
        T->balFactor = RH;
        T1->balFactor = EH;
        break;
    case EH:
        T->balFactor = EH;
        T1->balFactor = EH;
        break;
    case RH:
        T->balFactor = EH;
        T1->balFactor = LH;
        break;
    }
    T2->balFactor = EH;
    T = T2;
}

//quay kep RL
void rotateRL(AVLTree& T) {
    AVLNode* T1 = T->pRight;
    AVLNode* T2 = T1->pLeft;
    T->pRight = T2->pLeft;
    T2->pLeft = T;
    T1->pLeft = T2->pRight;
    T2->pRight = T1;
    switch (T2->balFactor) {
    case RH:
        T->balFactor = LH;
        T1->balFactor = EH;
        break;
    case EH:
        T->balFactor = EH;
        T1->balFactor = EH;
        break;
    case LH:
        T->balFactor = EH;
        T1->balFactor = RH;
        break;
    }
    T2->balFactor = EH;
    T = T2;
}

//can bang khi cay lech ve ben trai
int balanceLeft(AVLTree& T) {
    AVLNode* T1 = T->pLeft;
    switch (T1->balFactor) {
    case LH: rotateLL(T); return 2;
    case EH: rotateLL(T); return 1;
    case RH: rotateLR(T); return 2;
    }
    return 0;
}

//can bang khi cay lech ve ben phai
int balanceRight(AVLTree& T) {
    AVLNode* T1 = T->pRight;
    switch (T1->balFactor) {
    case LH: rotateRL(T); return 2;
    case EH: rotateRR(T); return 1;
    case RH: rotateRR(T); return 2;
    }
    return 0;
}
int insertNode(AVLTree& T, int X) {
    int res;
    if (T) {
        if (T->key == X) return 0;//da co gia tri
        if (T->key > X) {
            res = insertNode(T->pLeft, X);
            if (res < 2) return res;
            switch (T->balFactor) {
            case RH:
                T->balFactor = EH;
                return 1;
            case EH:
                T->balFactor = LH;
                return 2;
            case LH:
                balanceLeft(T);
                return 1;
            }
        }
        else {
            res = insertNode(T->pRight, X);
            if (res < 2) return res;
            switch (T->balFactor) {
            case LH:
                T->balFactor = EH;
                return 1;
            case EH:
                T->balFactor = RH;
                return 2;
            case RH:
                balanceRight(T);
                return 1;
            }
        }
    }
    T = new AVLNode;
    if (T == NULL) return -1; // thieu bo nho
    T->key = X;
    T->balFactor = EH;
    T->pLeft = T->pRight = NULL;
    return 2;
}
void randomTree(AVLTree& T, int a[], int n) {
    for (int i = 0; i < n; i++) {
        insertNode(T, a[i]);
    }
}
void randomnode(AVLTree& T) {
    srand(time(NULL));   
    int r = rand();
    insertNode(T, r);
}
void displayTree(AVLTree T, int level = 0) {
    if (T == nullptr) return;
    displayTree(T->pRight, level + 1);
    for (int i = 0; i < level; i++) printf("   ");
    printf("%d(%d) \n", T->key, T->balFactor);
    displayTree(T->pLeft, level + 1);
}
int main() {
    AVLTree tree = nullptr;
    int a[] = { 4, 6,3,7, 11, 24 };
    int n = sizeof(a) / sizeof(a[0]);
    randomTree(tree, a, n);
    randomnode(tree);
    displayTree(tree);
}
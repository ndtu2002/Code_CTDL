#define _crt_secure_no_deprecate
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 100

int min(int a, int b) {
    if (a > b) {
        return b;
    }
    else return a;
}
void Distribute(float a[], int n, int& pb, int& pc,int k, int b[], int c[]) {
    int i, p;
    // tach a thanh b va c
    p = pb = pc = 0;
    while (p < n) {
        // phan phôi luan phien day a vao b va c
        for (i = 0; (p < n) && (i < k); i++)
            b[pb++] = a[p++];
        for (i = 0; (p < n) && (i < k); i++)
            c[pc++] = a[p++];
    }
}
void Merge(float a[], int nb, int nc, int k, int b[], int c[]) {
    int p, pb, pc, ib, ic, kb, kc;
    p = pb = pc = 0;
    ib = ic = 0;
    while ((0 < nb) && (0 < nc)) {
        kb = min(k, nb); kc = min(k, nc);
        if (b[pb + ib] <= c[pc + ic]) {
            a[p++] = b[pb + ib];
            ib++;
            if (ib == kb) {
                for (; ic < kc; ic++)
                    a[p++] = c[pc + ic];
                pb += kb; pc += kc;
                ib = ic = 0;
                nb -= kb; nc -= kc;
            }
        }
        else {
            a[p++] = c[pc + ic];
            ic++;
            if (ic == kc) {
                for (; ib < kb; ib++)
                    a[p++] = b[pb + ib];
                pb += kb; pc += kc;
                ib = ic = 0;
                nb -= kb; nc -= kc;
            }
        }
    }
}

void MergeSort(float a[], int n) {
   int b[MAX];
   int c[MAX];
   int p, pb, pc; //cac chi so tren cac mang a, b, c
   int i, k = 1;  //do dai cua day con khi phan hoach
   do {
     Distribute(a, n, pb, pc, k, b, c);
     Merge(a, pb, pc, k, b, c);
     k *= 2;
   } while (k < n);
}
struct SinhVien {
	char hoTen[20];
	char maSV[20];
	float diem[5];
};
void swap(float* a, float* b)
{

	int temp = *a;
	*a = *b;
	*b = temp;
}
void sortDiem(SinhVien& sv) {
	MergeSort(sv.diem, 5);
}
void nhap(SinhVien& sv) {
	printf("Nhap ten: ");
	fflush(stdin);
	fgets(sv.hoTen, 20, stdin);
	printf("Nhap ma so: ");
	fgets(sv.maSV, 10, stdin);
	for (int i = 0; i < 5; i++) {
		printf("Mon %d: ", i + 1);
		scanf_s("%f", &sv.diem[i]);
	}
	getchar();
}
void nhapMangSV(SinhVien sv[], int n) {
	for (int i = 0; i < n; i++) {
		printf("Nhap sinh vien thu %d: \n", i + 1);
		nhap(sv[i]);
	}
}

void xuat(SinhVien sv) {
	printf("\nHo va ten sinh vien: \n");
	printf("%s", sv.hoTen);
	printf("Ma so sinh vien: \n");
	printf("%s", sv.maSV);
	printf("Diem 5 mon: \n");
	for (int i = 0; i < 5; i++) {
		printf("Mon %d: \n", i + 1);
		sortDiem(sv);
		printf("%f\n", sv.diem[i]);
	}
}
void xuatMangSV(SinhVien sv[], int n) {
	for (int i = 0; i < n; i++) {
		printf("Sinh vien thu %d: ", i + 1);
		xuat(sv[i]);
	}
}
void checkMSSV(SinhVien sv[], int n) {
	char mssv[20];
	printf("Nhap ma so can tim: ");
	fgets(mssv, 20, stdin);
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(mssv, sv[i].maSV) == 0) {
			xuat(sv[i]);
			flag = 1;
		}
	}
	if (flag == 0)
		printf("Khong thay");
}
void capNhatTen(SinhVien sv[], int n) {
	char mssv[20];
	printf("Nhap ma so can tim: ");
	fgets(mssv, 20, stdin);
	fflush(stdin);
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(mssv, sv[i].maSV) == 0) {
			fgets(sv[i].hoTen, 20, stdin);
			flag = 1;
		}
	}
	if (flag == 0)
		printf("Khong thay");
}
void printArray(int arr[], int N)
{
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main() {
	SinhVien sv[2];
	nhapMangSV(sv, 2);
	xuatMangSV(sv, 2);
	capNhatTen(sv, 2);
	xuatMangSV(sv, 2);
}

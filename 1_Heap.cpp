/*Đề 1: Cài đặt kiểu dữ liệu Sinh viên gồm :
+ Họ và tên : tối đã 20 kí tự.
+ Mã số sinh viên : 10 kí tự.
+ Điểm tổng kết 5 môn : mảng 5 phần tử kiểu số thực.
1. Viết hàm nhập thông tin sinh viên, tìm sinh viên theo MSSV, cập nhật lại tên sinh viên.
2. Viết hàm để cài đặt thuật toán Heap sort max để xếp tăng điểm trung bình của sinh viên.*/
#define _crt_secure_no_deprecate
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void heapify(float arr[], int N, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < N && arr[left] > arr[largest])
		largest = left;
	if (right < N && arr[right] > arr[largest])
		largest = right;
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, N, largest);
	}
}
void heapSort(float arr[], int N)
{
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);
	for (int i = N - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		heapify(arr, i, 0);
	}
}
void sortDiem(SinhVien& sv) {
	heapSort(sv.diem, 5);
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
	if(flag == 0)
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
void main() {
	SinhVien sv[3];
	nhapMangSV(sv, 3);
	xuatMangSV(sv, 3);
	capNhatTen(sv, 3);
	xuatMangSV(sv, 3);
}
/*Đề 3: Cài đặt kiểu dữ liệu Sinh viên gồm: 
1.  hàm để tạo và ghi một file gồm 10000 phần tử số nguyên.
2. Viết hàm để đọc file vừa tạo để lưu 10000 phần tử vào một mảng 1 chiều.
3. Viết hàm để cài đặt thuật toán Shell Sort cho mảng một chiều.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void GhiFile() {
    FILE* file = fopen("D:\\Visual project\\CTDL_GT\\On_Thi\\data.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot open file");
        return;
    }
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
        int randomNumber = rand();
        fprintf(file, "%d ", randomNumber);
    }
    fclose(file);
}
void DocFile(int a[]) {
    FILE* file = fopen("D:\\Visual project\\CTDL_GT\\On_Thi\\data.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open file");
        return;
    }
    for (int i = 0; i < 10000; i++) {
        fscanf(file, "%d", &a[i]);
    }

    fclose(file);
}
void taoh(int h[], int n) {//Tạo H với H là chuỗi số fibonaci
    h[0] = 0;
    h[1] = 1;
    for (int i = 2; i < n; i++) {
        h[i] = h[i - 1] + h[i - 2];
    }
}
void ShellSort(int a[], int N, int h[], int k)
{
    int step, i, j;
    int x, len, pos;
    for (step = 0; step < k; step++) {
        len = h[step];
        for (i = len; i < N; i++) {
            x = a[i];
            pos = i - len;//a[j] đứng kề trước a[i] trong cùng dãy con
            while ((x < a[pos]) && (pos >= 0)) { //Insertion Sort
                a[pos + len] = a[pos];
                pos = pos - len;
            }
            a[pos + len] = x;
        }
    }
}

int main() {
    int a[10000];
    //GhiFile();
    DocFile(a);

    int h[20];
    taoh(h, 20);
    ShellSort(a, 10000, h, 20);

        for (int i = 0; i < 10000; i++){
        printf("%d ", a[i]);
    }
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int Control_Sum(FILE* file) {
    int M = 255;
    int T = 0;
    char a;
    while (1) {
        if (fread(&a, 1, 1, file) != 1) {
            break;
        }
        T += (int)a;
    }
    return T % (M + 1);
}

int main()
{
    setlocale(LC_ALL, "ru");
    FILE* test;
    char Name_File[256] = { 0 };

    printf("Введите имя файла: ");
    scanf_s("%255s", Name_File, 255);

    fopen_s(&test,Name_File,"r");
    unsigned long long f = Control_Sum(test);
    printf("Control Sum = %llu", f);
    if (test) fclose(test);
}
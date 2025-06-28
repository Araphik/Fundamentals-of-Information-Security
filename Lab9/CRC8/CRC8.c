#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>
#include <malloc.h>
#define POLY 10010011


enum {CRC_S = 1, CRC_D = 2, EXIT = 3};
void CRC8_S();
void CRC8_D();

char buf[9] = { 0 };

int main() 
{
    setlocale(LC_ALL, "1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (1)
    {
        printf("        Что вы хотите сделать?    ");
        puts("\n");
        puts("      1) CRC - сдвигом ");
        puts("");
        puts("      2) CRC - полиномиальным деление ");
        puts("");
        puts("      3) Выход");

        int Choose = 0;
        scanf_s("%d", &Choose);
        switch (Choose)
        {
            case CRC_S:
            {
                system("cls");
                CRC8_S();
                return CRC_S;
            }

            case CRC_D:
            {
                system("cls");
                CRC8_D();

                return CRC_D;
            }

            case EXIT:
            {
                return EXIT;
            }
        
            default:
            {
                printf("Неправильный ввод! ");
                Sleep(500);
                system("cls");
            }

        }

    }
}

void CRC8_S()
{
    unsigned char crc = 0xff;
    int flag = 0;
    wchar_t a;
    char Name_File[256] = { 0 };
    printf("Введите имя файла: ");
    scanf_s("%255s", Name_File, 255);

    FILE* file = fopen(Name_File, "rb");
    while (1) 
    {
        if (fread(&a, 1, 1, file) != 1) 
        {
            break;
        }
        else 
        {
            flag = 1;
        }

        crc ^= (int)a;
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = ((crc << 1) ^ 1);
            }
            else {
                crc <<= 1;
            }
        }
    }
    if (flag == 0) {
        printf("0\n");
        return;
    }
    crc %= 256;
    crc ^= 0xff;
    if (crc < 0) crc = abs(crc)+1;
 
    char itog[255] = {0};
    _itoa_s(crc, itog, 255, 2);
    printf("Сдвигом:\nint -> %d\nbin -> %s\nhex -> %x\nsym -> %c\n", crc, itog, crc, (char)crc);
    fclose(file);
}

void CRC8_D()
{
    char Name_File[256] = { 0 };
    printf("Введите имя файла: ");
    scanf_s("%255s", Name_File, 255);
    FILE* file = fopen(Name_File, "rb");
    char Poly_String[8];
    int PolyVR = POLY;
    for (int p = 0; p < 8; p++) {
        Poly_String[7 - p] = PolyVR % 10;
         PolyVR /= 10;
    }

    fseek(file, 0, SEEK_END);
    int Size_File = ftell(file);
    rewind(file);

    unsigned char* Text_File = (unsigned char*)malloc((Size_File + 1) * sizeof(unsigned char));
   
    Text_File[Size_File] = '\0';
    for (int p = 0; p < Size_File; p++) 
        fscanf(file, "%c", &Text_File[p]);

    unsigned char Poly_Char = 0;

    for (int p = 0; p < 8; p++)
    {
        if (Poly_String[p] == 1)
            Poly_Char = Poly_Char | (1 << (7 - p));
    }
   
    unsigned char Buffer = 0;
    while(Size_File--)
    {
        Buffer = Buffer ^ *Text_File++;

        for (int p = 0; p < 8; p++)
        {
            if (Buffer & 0x80)
            {
                Buffer = (Buffer << 1) ^ Poly_Char;
            }
            else Buffer <<= 1;
        }
    }

    int CRC_10 = Buffer;
    char CRC_2[16] = {0};
    _itoa_s(CRC_10, CRC_2, 15, 2);

    printf("DEC = %d\nHEX = %x\nSYM = %c\nBIN = %s\n", CRC_10, CRC_10, CRC_10, CRC_2);
    fclose(file);
}

   


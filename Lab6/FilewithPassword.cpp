#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <TIME.H>
#include <windows.h>

#define PASSWORD 1
#define CHANGE 2
#define EXIT 3

int flag = 0;

void Proverka(char* enter, char* password, int choose, FILE* pass)
{
	if (choose == PASSWORD)
	{
		if (strcmp(enter, password) == NULL)
		{
			printf("Password right!\n");
			system("C:\\text.txt");
		}
		else
		{
			printf("Password wrong! Try again");
			for (int i = 0; i < 3; i++)
			{
				printf(".");
				Sleep(1000);
			}
		}
	}
	if (choose == CHANGE)
	{
		if (flag == 1)
		{
			printf("Введите новый пароль: ");
			memset(enter, 0, 256);
			scanf_s("%257s", enter, 256);
			pass = fopen("password.txt", "w");
			fputs(enter, pass);
			Sleep(1000);
			printf("Пароль сменен успешно");
			for (int i = 0; i < 3; i++)
			{
				printf(".");
				Sleep(500);
			}
			fclose(pass);
			flag = 0;
			system("cls");
		}
		else
		{
			printf("Введите пароль: ");
			scanf_s("%257s", enter, 256);
			system("cls");
			if (strcmp(enter, password) == NULL)
			{
				printf("Введите новый пароль: ");
				memset(enter, 0, 256);
				scanf_s("%257s", enter, 256);
				pass = fopen("password.txt", "w");
				fputs(enter, pass);
				Sleep(1000);
				printf("Пароль сменен успешно");
				for (int i = 0; i < 3; i++)
				{
					printf(".");
					Sleep(500);
				}
				fclose(pass);
				flag = 0;
				system("cls");
			}
			else
			{
				printf("Введен неверный пароль! Попробуйте еще раз");
				for (int i = 0; i < 3; i++)
				{
					printf(".");
					Sleep(500);
				}
				fclose(pass);
				system("cls");
			}
		}

	}

}

int main()
{
	char password[257] = { 0 };
	int choose = 0;
	setlocale(LC_ALL, "Rus");
	FILE* pass;
    l1:
	pass = fopen("password.txt", "r");
	fseek(pass, 0, SEEK_END);
	if (ftell(pass) == 0)
		flag = 1;
	fseek(pass, 0, SEEK_SET);
	fgets(password, 256, pass);
	printf("-------------------------------\n");
	printf("|                             |\n");
	printf("|     Что вы хотите сделать?  |\n");
	printf("|                             |\n");
	printf("|  1) Получить доступ к файл  |\n");
	printf("|                             |\n");
	printf("|  2) Поменять пароль         |\n");
	printf("|                             |\n");
	printf("|  3) Выйти из программы      |\n");
	printf("|                             |\n");
	printf("-------------------------------\n");
	printf("ВВОД: ");
	scanf_s("%d", &choose);
	system("cls");
	switch (choose)
	{
	case PASSWORD:
	{
		char enter[257];
		printf("Введите пароль: ");
		scanf_s("%257s", enter, 256);
		Proverka(enter, password, choose, pass);
		system("cls");
		fclose(pass);
		goto l1;
	}

	case CHANGE:
	{
		char enter[257];
		Proverka(enter, password, choose, pass);
		system("cls");
		goto l1;
	}

	case EXIT:
	{
		break;
	}

	default:
	{
		goto l1;
	}
	}
}
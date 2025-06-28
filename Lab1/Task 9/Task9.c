#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>


int Evklid(int a, int b)
{

	while (a && b)
	{
		if (a > b)
			a = a - (a / b) * b;
		else
			b = b - (b / a) * a;
	}

	if (b > a) a = b;
	if (a == 1)
		return 1;
	else return 0;

}

int Binary(int a, int openkey[])
{
	if (a >= 0)
	{
		int shifor = 0;
		for (int i = 7; i >= 0; i--)
		{
			if (a % 2 == 1)
				shifor += openkey[i];
			a /= 2;
		}
		return shifor;
	}
	else
	{
		a = abs(a)-1;
		int shifor = 0;
		for (int i = 7; i >= 0; i--)
		{
			if (a % 2 == 0)
				shifor += openkey[i];
			a /= 2;
		}
		return shifor;
	}
	
}

int Desh(int closekey[], int itog, int m)
{
	for (int i = 0; i < 256; i++)
	{
		int x = i, k = 0, sum = 0, bin[8] = { 0 }, j = 7;

		for (int v = 7; v >= 0; v--) { b.0in[v] = x % 2; x /= 2; }

		for (int v = 0; v < 8; v++) if (bin[v] == 1) sum += closekey[v];

		if (sum == itog)
		{
			sum = 0;
			int p = 0;
			for (int v = 7; v >= 0; v--)
			{
				sum += bin[v] * pow(2,p);
				p++;
			}
			return sum;
		}
	}
}
void main()
{
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	char s[100];

	scanf_s("%100s", s, 99);
	int length = strlen(s);

	/// 
	/// Генерация закрытого ключа
	/// 

	unsigned int closekey[8] = { 0 };

	closekey[0] = rand() % 10;
	int sum = closekey[0];

	printf("Закрытый ключ: ");
	for (int i = 0; i < 8; i++)
	{
		closekey[i] = rand() % 10 + sum + 1;
		sum += closekey[i];
		printf("%d ", closekey[i]);
	}

	printf("\n");

	///
	/// Получение чисел m и n
	/// 

	int m = sum + rand() % 10;
	int n = rand() % 10 + 2;
	while (Evklid(n, m) == 0)
	{
		n = rand() % 10 + 2;
	}


	/// 
	/// Преобразование слова в ASCII код
	/// 

	int* nums;

	nums = (int*)malloc(length * sizeof(int));
	for (int i = 0; i < length; i++)
	{
		nums[i] = (int)s[i];
	}

	///
	/// Получение открытого ключа
	/// 

	unsigned int openkey[8] = { 0 };
	printf("Открытый ключ: ");
	for (int i = 0; i < 8; i++)
	{
		openkey[i] = (closekey[i] * n) % m;
		printf("%d ", openkey[i]);
	}

	printf("\n");


	///
	/// Получение шифрограммы
	/// 

	int* itog;
	itog = (int*)malloc(length * sizeof(int));

	printf("Шифрограмма: ");
	for (int i = 0; i < length; i++)
	{
		itog[i] = Binary(nums[i], openkey);
		printf("%d ", itog[i]);
	}

	printf("\n");

	///
	/// Дешифрование
	/// 

	int no = 0;

	while ((n * no) % m != 1)
	{
		no++;
	}

	int* deshifr;
	deshifr = (int*)malloc(length * sizeof(int));

	printf("Строка дешифрованая: ");

	for (int i = 0; i < length; i++)
	{
		itog[i] = itog[i] * no % m;
		printf("%d ", itog[i]);
	}
	printf("\n");

	for (int i = 0; i < length; i++)
	{
		deshifr[i] = Desh(closekey, itog[i], m);
		char sym = deshifr[i];
		printf("%d - %c       ", deshifr[i], sym);
	}
}

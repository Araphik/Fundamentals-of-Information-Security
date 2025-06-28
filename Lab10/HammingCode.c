#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <Windows.h>
#include <locale.h>
#include <string.h>

char file_input[] = "input.txt";///исходный файл
char file_coder[] = "coder2.txt";/// файл с закодированным текстом
char file_decoder[] = "decoder2.txt";/// файл с раскодированным текстом
int bin_len = 0;/// длина текста в битах
int sizeall = 0;/// длина в битах с учетом добавления контрольных бит
int controlbit[] = { 0,1,3,7,15,31,63 };/// "номера" контрольных бит
char* textbit; /// битовое представление текста
char* text; /// массив для записи

int coder()
{
	int block = 0;
	int size = 0;
	printf("Size of text block: ");
	scanf_s("%d", &block);//считываем размер кодируемых блоков
	if (razmer(block) == 0)
	{
		printf("Error\n");///если размер указан не верно выводится ошибка
		return 0;
	}
	size = razmer(block);
	text_to_bit(file_input);// преобразование в биты
	control(block, size);/// добавление контрольных бит
	create_file(file_coder);/// запись зокодированного текста в файл
	return 0;
}

int decoder()
{
	int block = 0;
	int	size = 0;
	printf("Size of text block: ");
	scanf_s("%d", &block);/// размер блоков
	if (razmer(block) == 0)
	{
		printf("Error\n");
		return 0;
	}
	text_to_bit(file_coder);// перевод закодированного текста в биты
	size = razmer(block);
	if ((bin_len % size) != 0) { /// если длина текста в битах не кратна размеру блока (с учетом контрольных бит) 
		int tmp_all = bin_len;//сохранение в памяти длины в битах
		bin_len = bin_len + (size - bin_len % size);//увеличение длины таким образом чтобы она была кратна размеру блока
		textbit = (char*)realloc(textbit, bin_len * sizeof(char));///обнуление контрольных бит
		for (int i = tmp_all; i < bin_len; i++)
			textbit[i] = 0;
	}
	sizeall = bin_len * block / size; ///размер без учета контрольных бит
	text = (char*)realloc(text, sizeall * sizeof(char));// выделение размера найденому в прошлой строке

	for (int i = 0; i < bin_len; i = i + size)///цикл проходит по тексту с шагом в блок
		proverka(i, size, block);

	for (int f = 0, m = 0; f < bin_len; f = f + size, m = m + block) /// цикл удаляет из текста контрольные биты 
	{
		int t = 0, j = 0, k = 0;
		while (t < block)
		{
			if (j == controlbit[k])
			{
				k++; j++;
			}
			else text[m + t++] = textbit[f + j++];
		}
	}
	create_file(file_decoder); ///создание и запить в файл 
	return 0;
}

int razmer(int x)/// функция возвращает размер блока с учетом добавления контрольных бит
//// это делается исходя из того какие биты являются контрольными в коде Хемминга
{
	int size = 0;
	if (x == 8) size = 12;
	if (x == 12) size = 17;
	if (x == 16) size = 21;
	if (x == 24) size = 29;
	if (x == 32) size = 38;
	if (x == 48) size = 54;
	if (x == 64) size = 71;
	return size;/// если размер введен не верно функция вернет 0
}

int text_to_bit(char* filename)
{
	FILE* text_file;
	fopen_s(&text_file, filename, "r");/// открытие исходного файла на чтение
	if (text_file == NULL) { printf("File no found"); return 0; }///если входной файл не найден завершаем работу программы и выводим ошибку
	while (!feof(text_file)) {//пока не конец файла
		int x = fgetc(text_file);//присваиваем х код символа из файла
		textbit = (char*)realloc(textbit, (bin_len + 8) * sizeof(char));/// выделение 8 бит для символа
		for (int i = 7; i >= 0; i--)///перевод кода символа в двоичный и запись в массив
		{
			textbit[bin_len + i] = x % 2;
			x = x / 2;
		}
		bin_len = bin_len + 8;//длина текста в двоичном виде
	}
	fclose(text_file);
	return 0;
}

int control(int block, int size)
{
	sizeall = bin_len / block * size;///размер с учетом добавления контрольных бит 
	if ((sizeall % size) != 0) sizeall = sizeall + (size - sizeall % size); // общая длина кратна размеру блока
	text = (char*)realloc(text, sizeall * sizeof(char));/// выделение памяти на контрольные биты
	for (int p = 0, j = 0; j < bin_len && p < sizeall; p = p + size)//// цикл проходит по всему тексту 
		//// р-по блокам с шагом равному размеру блока, j - по всему тексту с шагом 1
	{
		int k = 0;
		for (int i = 0; i < size; i++)/// цикл проходит по блоку
		{
			if (i == controlbit[k])/// если номер бита равен контрольному
			{
				text[p + i] = 0; k++; /// то этому биту в тексте присваивается 0
			}
			else if (j < bin_len)
				text[p + i] = textbit[j++];/// если бит не контрольный то он переписывается из исходного текста
			else text[p + i] = 0;///если весь текст уже переписан присваивается 0
		}
		bity(p, size, block);///вычисление контрольного бита
	}
	return 0;
}

int bity(int p, int size, int block)
{
	int kolvo = size - block;/// кол-во контрольных бит в блоке
	int	ctrl_bit[7] = { 0 };

	for (int q = 0; q < kolvo; q++)
	{
		int start = controlbit[q]; ///номер контрольного бита в блоке
		int	shift = pow(2, q);/// 2 в степени q, шаг для вычисления контрольной суммы
		for (int i = start; i < size; i = i + shift + 1)/// вычисление суммы информационных бит для установления значения контрольного бита
			/// исходя из кода Хемминга
		{
			for (int j = i; j < shift && j < size; j++)
				ctrl_bit[q] = ctrl_bit[q] + text[p + j];
		}
	}

	for (int q = 0; q < kolvo; q++)///установка контрольного бита
	{
		ctrl_bit[q] = ctrl_bit[q] % 2;
		text[p + controlbit[q]] = ctrl_bit[q];
	}
	return 0;
}

int proverka(int p, int size, int block)
{
	int kolvo = size - block;/// кол-во контрольных бит в блоке
	int	h = 0;/// счетчик для подсчета несовпадающих контрольных бит 
	int	newkontrol[7] = { 0 };
	int	kontrolnye[7] = { 0 };
	for (int q = 0; q < kolvo; q++)//// цикл переписывает значения контрольных бит из текста в отдельный массив
		kontrolnye[q] = textbit[p + controlbit[q]];
	for (int q = 0; q < kolvo; q++)
	{
		int peviy = controlbit[q];/// контрольный бит для которого считается сумма 
		int	shag = pow(2, q);//шаг для счета суммы информационных бит
		for (int i = peviy; i < size; i = i + shag + 1) /// двойной цикл для подсчета значения контрольного бита 
			/// что бы при не совпадении можно было выявить ошибку
			for (int j = i; j < shag && j < size; j++)
				newkontrol[q] = newkontrol[q] + textbit[p + j];
	}
	for (int q = 0; q < kolvo; q++)
		if (newkontrol[q] != kontrolnye[q])/// проверка совпадает ли вычесленный контрольныйй бит с имеющимся 
			h = h + controlbit[q];///вычисление номера ошибочного бита 
	h++;
	if (h > size)
		h = 0;
	if (h > 0)
		textbit[p + h] = 1 - textbit[p + h];///если значение больше 0 (те в бите есть ошибка, то 
	return 0;
}

int create_file(char* name_of_file)
{
	FILE* file;
	fopen_s(&file, name_of_file, "wb+");
	for (int i = 0; i < sizeall; i = i + 8)// цикл проходит по байтам
	{
		if ((i + 8) > sizeall)
			break;/// если мы прошли все байты то выходим из цикла
		int a = 0;
		for (int j = 0; j < 8; j++)/// цикл проходит побитово по байту
			a = a + (int)text[i + j] * (int)pow(2, 7 - j); // преобразование одного байта в код символа
		fputc((char)a, file);// запись символа в файл
	}
	fclose(file);
	return 0;
}



int main()
{
	setlocale(LC_ALL, "Rus");/// локализация кириллицы в консоли 
	int n;
	printf("1-Code\n2-Decode\n3-Break\n");/// меню выбора операции
	scanf("%d", &n);
	if (n == 1) coder();//кодирование
	if (n == 2) decoder();///декодировани
	if (n == 3) return 0;///выход
	return 0;
}


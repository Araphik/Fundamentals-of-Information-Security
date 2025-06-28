#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>;
#include <stdlib.h>

unsigned int Crc32(unsigned char* str, unsigned long long len) //сдвиговые операции
{
	unsigned long long crc;
	unsigned char i;
	while (len--)
	{
		crc ^= *str << 8;
		for (i = 0; i < 8; i++)
			crc = crc & 0x80000000 ? (crc << 1) ^ 0x1 : crc << 1;

	}
	return crc;
}

int main()
{
	unsigned long int a = 0;
	unsigned long len = 0;
	unsigned char* str = NULL;
	int ch;
	FILE* file;
	fopen_s(&file, "input.txt", "r + b");
	while (!feof(file))
	{
		ch = fgetc(file);
		len++;
	}
	len -= 1;
	rewind(file);
	str = (unsigned char*)calloc(len, sizeof(char));
	while (!feof(file))
	{
		str[a] = fgetc(file);
		a++;
	}
	printf("CRC = %x\n", Crc32(str, len));
	fclose(file);

	return 0;
}


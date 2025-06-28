#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#define COMPLETED 0
#define CODER 1
#define DECODER 2
#define EXIT 3
#define ERROR_OPENING_THE_FILE 4
#define ERROR_LARGE_TEXT_SIZE 5

typedef struct {
	FILE* Text;
	FILE* Input;
	FILE* Output;
} Files;
unsigned int FileSize(FILE* File) {
	int Size = 0; 
	fseek(File, 0, SEEK_END); // перенос указателя в конец
	Size = ftell(File); // считывание указателя на файл
	fseek(File, 0, SEEK_SET); // перенос указателя в начало
	return(Size); 
}
void Heading(FILE* Input, FILE* Output) {
	char Symbol = 0;
	for (int i = 0; i < 49; i++) {
		fread(&Symbol, 1, 1, Input); // считываем побайтово заголок файла
		fwrite(&Symbol, 1, 1, Output); // переписываем побайтово заголовок в новый файл
	}
}
int PackingDegree() {
	int Degree = 0;
	while (1) {
		printf("Введите степень упаковки сообщения: 1, 2, 4 или 8\n");
		scanf_s("%d", &Degree); 
		while ((getchar()) != '\n');
		if (Degree == 1 || Degree == 2 || Degree == 4 || Degree == 8) break;
	}
	return Degree;
}
void InformationText(int Degree, int SizeText, FILE* Output) {
	unsigned int Size = 0;
	fwrite(&Degree, 1, 1, Output);
	for (int i = 3; i >= 0; i--) {
		Size = SizeText; 
		Size = Size >> (8 * i); 
		Size = Size & 255; // сопоставление с маской
		fwrite(&Size, 1, 1, Output); // переписываем маску 
	}
}
void TextEncoding(FILE* Input, FILE* Output, FILE* Text, int Degree) {
	char TextSymbol, Symbol, ImgSymbol;
	unsigned char ImgMask = 255 << Degree;
	unsigned char TextMask = 255 >> (8 - Degree);
	while (!feof(Text)) {
		fread(&TextSymbol, 1, 1, Text);
		if (!feof(Text)) {
			for (int i = 8 / Degree - 1; i >= 0; i--) {
				Symbol = TextSymbol;
				Symbol = Symbol >> Degree * i;
				Symbol = Symbol & TextMask;
				fread(&ImgSymbol, 1, 1, Input);
				ImgSymbol = ImgSymbol & ImgMask;
				ImgSymbol = ImgSymbol | Symbol;
				if (!feof(Text)) fwrite(&ImgSymbol, 1, 1, Output);
			}
		}
	}
	while (!feof(Input)) {
		fread(&ImgSymbol, 1, 1, Input);
		if (!feof(Input)) fwrite(&ImgSymbol, 1, 1, Output);
	}
}
int MaxSize(unsigned int SizeText, unsigned int SizePicture, int Degree) {
	if (SizeText >= (SizePicture * (unsigned int)Degree / 8 - 54)) {
		printf("Размер выбранного текста больше, чем возможно упаковать в контейнер\n");
		return ERROR_LARGE_TEXT_SIZE;
	}
	return COMPLETED;
}
int CheckFiles(FILE* File) {
	if (File == NULL) {
		printf("Ошибка при открытии файла\n");
		return ERROR_OPENING_THE_FILE;
	}
	return COMPLETED;
}
int NumberOfCharacters(FILE* Output) {
	int Quantity = 0;
	unsigned char  Symbol = 0;
	unsigned int Size = 0;
	for (int i = 3; i >= 0; i--) {
		fread(&Symbol, 1, 1, Output);
		Size = (unsigned int)Symbol;
		Size = Size << (8 * i);
		Quantity = Quantity | Size;
	}
	return Quantity;
}
void PrintInformation(unsigned int Quantity, int Degree, FILE* Output, FILE* Text) {
	char Symbol = 0, ImgSymbol = 0;
	char ImgMask = ~(255 << Degree);
	for (unsigned int j = 0; j < Quantity; j++) {
		Symbol = 0;
		for (int i = 8 / Degree - 1; i >= 0; i--) {
			if (!feof(Output)) fread(&ImgSymbol, 1, 1, Output);
			if (!feof(Output)) {
				ImgSymbol = ImgSymbol & ImgMask;
				ImgSymbol = ImgSymbol << Degree * i;
				Symbol = Symbol | ImgSymbol;
			}
		}
		fwrite(&Symbol, 1, 1, Text);
	}
}
int Coder() {
	int Degree;
	unsigned int SizeText, SizePicture;
	Files OpenFile;
	Degree = PackingDegree(); // степень упаковки
	OpenFile.Input = fopen("1232.pptx", "rb"); // открываем исходное изображение 
	OpenFile.Output = fopen("2.bmp", "wb+"); // открываем выходное изображение
	OpenFile.Text = fopen("text.txt", "rb"); // открываем текст который шифруешь 
	if (CheckFiles(OpenFile.Input)) return ERROR_OPENING_THE_FILE;
	if (CheckFiles(OpenFile.Output)) return ERROR_OPENING_THE_FILE; //проверка файлов
	if (CheckFiles(OpenFile.Text)) return ERROR_OPENING_THE_FILE;
	SizeText = FileSize(OpenFile.Text); // подсчет разимера файла в байтах
	SizePicture = FileSize(OpenFile.Input); // подсчкет размера файла в байтах
	if (MaxSize(SizeText, SizePicture, Degree)) return ERROR_LARGE_TEXT_SIZE; // проверка что текстовое сообщение можно закоджировать в битах изображения
	Heading(OpenFile.Input, OpenFile.Output); // перепись заголовка изображения в новый файл
	InformationText(Degree, SizeText, OpenFile.Output); // перепись основной части изображенния в новый файл
	fseek(OpenFile.Input, 5, SEEK_CUR); // сдвиг на 5 от текущей позиции курсора 
	TextEncoding(OpenFile.Input, OpenFile.Output, OpenFile.Text, Degree); // кодирования текста сообщения в новый BMP файл
	fclose(OpenFile.Input);
	fclose(OpenFile.Output);
	fclose(OpenFile.Text);
	return COMPLETED;
}
int Decoder() {
	int Degree;
	unsigned int Quantity = 0;
	Files OpenFile;
	OpenFile.Output = fopen("output.bmp", "rb"); //открываем файл декодированнного сообщения
	OpenFile.Text = fopen("message.txt", "wb"); //открываем файл который кодируем 
	if (CheckFiles(OpenFile.Output)) return ERROR_OPENING_THE_FILE; // проверка файла на целостность
	if (CheckFiles(OpenFile.Text)) return ERROR_OPENING_THE_FILE;
	fseek(OpenFile.Output, 49, SEEK_SET); 
	Degree = fgetc(OpenFile.Output);
	Quantity = NumberOfCharacters(OpenFile.Output); //определение какое количества можно добавить 
	PrintInformation(Quantity, Degree, OpenFile.Output, OpenFile.Text); // декодирование изображения
	fclose(OpenFile.Output);
	fclose(OpenFile.Text);
	return COMPLETED;
}
void Menu() {
	int Choice = 0;
	while (1) {
		printf("------------------------------------------\n");
		printf("-   +++++++++++++++++++++++++++++++++    -\n");
		printf("-         Что вы хотите сделать?         -\n");
		printf("-   +++++++++++++++++++++++++++++++++    -\n");
		printf("------------------------------------------\n");
		printf("------------------------------------------\n");
		printf("-                                        -\n");
		printf("-  |1|  для выбора сокрытия текста       -\n");
		printf("-                                        -\n");
		printf("-  |2|  для выбора извлечение сообщения  -\n");
		printf("-                                        -\n");
		printf("-  |3|  выход из программы               -\n");
		printf("-                                        -\n");
		printf("------------------------------------------\n");
		printf("Ввод: ");
		scanf_s("%d", &Choice);
		system("cls");
		while ((getchar()) != '\n');
		if (Choice == CODER || Choice == DECODER || Choice == EXIT) {
			if (Choice == EXIT) break;
			if (Choice == CODER) {
				Coder();
				continue;
			}
			if (Choice == DECODER) {
				Decoder();
				continue;
			}
		}
		else printf("Ошибка ввода, попробуйте еще раз:");
	}
}
int main() {
	setlocale(LC_ALL, "Rus");
	Menu();
	return COMPLETED;
}

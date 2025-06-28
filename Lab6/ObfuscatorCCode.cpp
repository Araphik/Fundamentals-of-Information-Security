#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#define InputFile 1
#define OutputFile 2
#define MaxSizeName 100
#define end !feof(Input)
#define Quotation '\"'
#define SingleQuotation '\''
#define Hash '#'
#define Equal '='
#define Sum '+'
#define NewLine '\n'
#define Space ' '
#define Semicolon ';'
#define Slash '/'
#define Asterisk '*'
#define Backslash '\\'
#define Tab '\t'
#define EndOfLine '\0'
long SizeArr(FILE* Input) {
	long Size = 0;
	fseek(Input, 0, SEEK_END);
	Size = ftell(Input);
	fseek(Input, 0, SEEK_SET);
	return Size;
}
void DeletingComments(FILE* Input, char* Arr) {
	char Sym = 0;
	char Bol = 0;
	int K = 1;
	int Count = 1;
	int Number = 0;
	while (end) {
		K = 1;
		Sym = (char)fgetc(Input);
		if (end) {
			if (Sym == Slash) {
				Bol = (char)fgetc(Input);
				if (Bol == Asterisk) {
					Bol = (char)fgetc(Input);
					while (end) {
						if (Bol == Asterisk) {
							Bol = (char)fgetc(Input);

							if (Bol == Slash) {
								Count++;
								break;
							}
						}
						if (Bol == Asterisk) continue;
						Bol = (char)fgetc(Input);
					}
					if (feof(Input)) break;
					if (Count != 1) {
						Count = 1;
						continue;
					}
				}
				if (Bol == Slash) {
					while (end) {
						Bol = (char)fgetc(Input);
						while (Bol == Backslash) {
							Bol = (char)fgetc(Input);
							if (Bol == NewLine) {
								Arr[Number] = Bol;
								Number++;
								Bol = (char)fgetc(Input);
								continue;
							}
						}
						if (Bol == NewLine) {
							if (end) {
								Arr[Number] = Bol;
								break;
							}
						}
					}
				}
				else {
					Arr[Number] = Sym;
					Number++;
					Sym = Bol;
				}
			}

			if (Sym == SingleQuotation) {
				if (end) {
					Arr[Number] = Sym;
					Number++;
				}
				while (end) {
					Sym = (char)fgetc(Input);
					if (end) {
						Arr[Number] = Sym;
						Number++;
					}
					while (Sym == Backslash) {
						K++;
						Sym = (char)fgetc(Input);
						if (end) {
							Arr[Number] = Sym;
							Number++;
						}
						if (K > 1 && K % 2 == 0 && Sym == SingleQuotation) break;
					}
					if (K % 2 != 0 && Sym == SingleQuotation) break;
					if (Sym == NewLine) break;
					K = 1;
				}
			}

			if (Sym == Quotation) {
				if (end) {
					Arr[Number] = Sym;
					Number++;
				}
				while (end) {
					Sym = (char)fgetc(Input);
					if (end) {
						Arr[Number] = Sym;
						Number++;
					}
					if (Sym == Quotation) break;
					if (Sym == NewLine) break;
					while (Sym == Backslash) {
						K++;
						Sym = (char)fgetc(Input);
						if (K % 2 != 0 && Sym == NewLine) break;
						if (end) {
							Arr[Number] = Sym;
							Number++;
						}
						if (K % 2 == 0 && Sym == Quotation) break;
					}
					if (K % 2 != 0 && Sym == Quotation) break;
					if (K % 2 != 0 && Sym == NewLine) break;
					K = 1;
				}
			}
			if (end && Sym != Quotation && Sym != SingleQuotation && Sym != Slash) {
				Arr[Number] = Sym;
				Number++;
				continue;
			}
		}
	}
	Arr[Number] = EndOfLine;
}
void PrintText(char* Text, unsigned long long Size, FILE* Output) {
	char Replacement[100][25] = { 0 };
	char VariablesArr[100][25] = { 0 };
	int FlagContinue = 0, FlagWord = 0, FlagRubbish1 = 0, FlagRubbish2 = 0;
	FILE* VariablesFile = fopen("Variables.txt", "r");
	FILE* UseVariables = fopen("Var.txt", "r");
	for (int i = 0; i < 100 && !feof(VariablesFile); i++) if (fscanf(VariablesFile, "%s", Replacement[i]) == 0) return;
	for (int i = 0; i < 100 && !feof(UseVariables); i++) if (fscanf(UseVariables, "%s", VariablesArr[i]) == 0)return;
	char String[25] = { 0 };
	int j = 0;
	for (unsigned long long i = 0; i < Size; i++) {
		memset(String, 0, 25);
		j = 0;
		if (Text[i] == 0) continue;
		if (FlagRubbish1 == 0 && Text[i] == '{') {
			fprintf(Output, "%c", Text[i]);
			fprintf(Output, "%s", "int kgjrghrhyghr=0;int gjrhegvgyy=0;for(int lgrkgjr=0;lgrkgjr<10;lgrkgjr++)kgjrghrhyghr+=gjrhegvgyy;");
			FlagRubbish1 = 1;
			continue;
		}
		if (FlagRubbish2 == 0 && Text[i] == '{') {
			fprintf(Output, "%c", Text[i]);
			fprintf(Output, "%s", "long krkgkrgfef=0; while(krkgkrgfef!=21)krkgkrgfef++;");
			FlagRubbish2 = 1;
			continue;
		}
		if ((Text[i] >= 0 && Text[i] <= 47) || (Text[i] >= 58 && Text[i] <= 64) || (Text[i] >= 91 && Text[i] <= 94) || Text[i] == 96 || (Text[i] >= 123 && Text[i] <= 126)) {
			fprintf(Output, "%c", Text[i]);
			continue;
		}
		while (Text[i] == 0 || Text[i] == 39 || (Text[i] >= 65 && Text[i] <= 90) || (Text[i] >= 97 && Text[i] <= 122) || Text[i] == 95 || (Text[i] >= 48 && Text[i] <= 57) || (Text[i] >= 128 && Text[i] <= 159) || (Text[i] >= 192 && Text[i] <= 255)) {
			String[j] = Text[i];
			j++;
			i++;
			FlagWord = 1;
		}
		if (FlagWord) {
			FlagWord = 0;
			i--;
		}
		if (strcmp(String, "_CRT_SECURE_NO_WARNINGS") == 0 || strcmp(String, "main") == 0) {
			fprintf(Output, "%s", String);
			continue;
		}
		for (int p = 0; p < 100 && VariablesArr[p][0] != EndOfLine; p++) {
			if (strcmp(String, VariablesArr[p]) == 0) {
				fprintf(Output, "%s", Replacement[p]);
				FlagContinue = 1;
				break;
			}
		}
		if (FlagContinue) {
			FlagContinue = 0;
			continue;
		}
		fprintf(Output, "%s", String);
	}
	remove("Var.txt");
	fclose(UseVariables);
}
int CheckFiles(FILE* Output) {
	if (Output == NULL) {
		printf("Error opening the file\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
void GetNameFile(int Parameter, char* NameFile) {
	if (Parameter == InputFile) printf("Enter the name of the input file:\n");
	if (Parameter == OutputFile) printf("Enter the name of the output file:\n");
	if (scanf("%s", NameFile) == 0)return;
}
void DeleteSpaceTabLine(unsigned long long Size, char* Text) {
	int Count = 0, Flag = 0;
	for (unsigned
		long long i = 0; i < Size; i++) {
		if (Text[i] == Hash) {
			Flag = 1;
		}
		if (Text[i] == NewLine) {
			if (Flag == 0) Text[i] = 0;
			else Flag = 0;
		}
		if (Flag == 1) continue;
		if (Text[i] == Tab) Text[i] = 0;
		if ((Text[i] >= 0 && Text[i] <= 47) || (Text[i] >= 58 && Text[i] <= 64) || (Text[i] >= 91 && Text[i] <= 96) || (Text[i] >= 123 && Text[i] <= 126)) { //ASCII коды знаков препинания, арифметических знаков, скобок
			Count = 1;
			while (i - Count > 0 && Text[i - Count] == Space) {
				Text[i - Count] = 0;
				Count++;
			}
			Count = 1;
			while (i + Count < Size && Text[i + Count] == Space) {
				Text[i + Count] = 0;
				Count++;
			}
		}
	}
}
void RenamingVariables(char* Text, unsigned long long Size) {
	char VariablesArr[100][25];
	for (int i = 0; i < 100; i++) memset(VariablesArr[i], 0, 20);
	char String[25] = { 0 };
	int Flag = 0, j = 0;
	int FlagString = 1;
	for (unsigned long long i = 0; i < Size; i++) {
		memset(String, 0, 25);
		j = 0;
		if (i + 4 < Size && Text[i] == Hash && Text[i + 1] == 'd' && Text[i + 2] == 'e' && (Text[i + 3] == 'f' && Text[i + 4] == 'i' && Text[i + 5] == 'n' && Text[i + 6] == 'e' && Text[i + 7] == Space)) Flag = 8;
		if (i + 4 < Size && Text[i] == 'i' && Text[i + 1] == 'n' && Text[i + 2] == 't' && (Text[i + 3] == Space || Text[i + 3] == Asterisk)) Flag = 4;
		if (i + 5 < Size && Text[i] == 'v' && Text[i + 1] == 'o' && Text[i + 2] == 'i' && Text[i + 3] == 'd' && (Text[i + 4] == Space || Text[i + 4] == Asterisk))Flag = 5;
		if (i + 5 < Size && Text[i] == 'c' && Text[i + 1] == 'h' && Text[i + 2] == 'a' && Text[i + 3] == 'r' && (Text[i + 4] == Space || Text[i + 4] == Asterisk))Flag = 5;
		if (i + 5 < Size && Text[i] == 'F' && Text[i + 1] == 'I' && Text[i + 2] == 'L' && Text[i + 3] == 'E' && Text[i + 4] == Asterisk)Flag = 5;
		if (i + 5 < Size && Text[i] == 'l' && Text[i + 1] == 'o' && Text[i + 2] == 'n' && Text[i + 3] == 'g' && Text[i + 4] == Space || Text[i + 4] == Asterisk)Flag = 5;
		if (i + 7 < Size && Text[i] == 'd' && Text[i + 1] == 'o' && Text[i + 2] == 'u' && Text[i + 3] == 'b' && Text[i + 4] == 'l' && Text[i + 5] == 'e' && Text[i + 6] == Space || Text[i + 6] == Asterisk)Flag = 7;
		if (i + 6 < Size && Text[i] == 'f' && Text[i + 1] == 'l' && Text[i + 2] == 'o' && Text[i + 3] == 'a' && Text[i + 4] == 't' && Text[i + 5] == Space || Text[i + 5] == Asterisk)Flag = 6;
		if (i + 9 < Size && Text[i] == 'l' && Text[i + 1] == 'o' && Text[i + 2] == 'n' && Text[i + 3] == 'g' && Text[i + 4] == Space && Text[i + 5] == 'l' && Text[i + 6] == 'o' && Text[i + 7] == 'n' && Text[i + 8] == 'g' && Text[i + 9] == Space || Text[i + 9] == Asterisk)Flag = 9;
		if (Flag > 0) {
			i += Flag;
			for (j = 0; Text[i] == 0 || (Text[i] >= 65 && Text[i] <= 90) || (Text[i] >= 97 && Text[i] <= 122) || Text[i] == 95 || (Text[i] >= 48 && Text[i] <= 57) && j < 25; j++, i++) {
				if (Text[i] != EndOfLine)String[j] = Text[i];
				else j--;
			}
			for (int p = 0; p < 100 && VariablesArr[p][0] != EndOfLine; p++) {
				if (strcmp(VariablesArr[p], String) == 0) FlagString = 0;
			}
			if (FlagString) {
				for (int p = 0; p < 100; p++) {
					if (VariablesArr[p][0] == EndOfLine) {
						strncpy(VariablesArr[p], String, 20);
						break;
					}
				}
			}
			FlagString = 1;
			Flag = 0;
		}
	}
	FILE* UseVariables = fopen("Var.txt", "w");
	if (UseVariables != NULL)
		for (int i = 0; i < 100; i++) fprintf(UseVariables, "%s\n", VariablesArr[i]);
	if (UseVariables != NULL) fclose(UseVariables);
}
void Action(void) {
	char NameInput[MaxSizeName];
	char NameOutput[MaxSizeName], * Text;
	FILE* Input = NULL;
	FILE* Output = NULL;
	unsigned long long Size = 0;
	memset(NameInput, 0, MaxSizeName);
	GetNameFile(InputFile, NameInput);
	Input = fopen(NameInput, "r");
	if (CheckFiles(Input)) return;
	GetNameFile(OutputFile, NameOutput);
	Output = fopen(NameOutput, "w");
	if (CheckFiles(Output)) return;
	Size = SizeArr(Input);
	Text = (char*)calloc((size_t)Size, sizeof(char));
	if (Text != NULL) {
		DeletingComments(Input, Text);
		fclose(Input);
		DeleteSpaceTabLine(Size, Text);
		RenamingVariables(Text, Size);
		PrintText(Text, Size, Output);
		fclose(Output);
	}
	free(Text);
}
int main(void) {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Action();
	return 0;
}
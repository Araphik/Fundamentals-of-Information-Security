#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h >
struct text
{
	char c;
	struct text* next;
};
void push_text(struct text* root, char txt) {
	struct text* tmp = (struct text*)malloc(sizeof(struct text));
	while (root->next != NULL) {
		root = root->next;
	}
	tmp->c = txt;
	tmp->next = root->next;
	root->next = tmp;
}

int main() {
	unsigned short POLY = 0x1;
	int i = 0, j;
	struct text* qwe = (struct text*)malloc(sizeof(struct text));
	FILE* original_file = NULL;
	unsigned char name_file[500];
	printf("enter file name: ");
	while (scanf("%c", &name_file[i])) 
	{
		if (name_file[i] == '\n')
			break;
		i++;
	}
	name_file[i] = '\0';
	original_file = fopen(name_file, "r");
	if (original_file != NULL) {
		unsigned char text_8;
		fscanf(original_file, "%c", &text_8);
		if (!feof(original_file)) {
			qwe->c = text_8;
			qwe->next = NULL;
			fscanf(original_file, "%c", &text_8);
			while (!feof(original_file)) {

				push_text(qwe, text_8);
				fscanf(original_file, "%c", &text_8);
			}

			unsigned short crc_16 = 0;
			while (qwe != NULL) {
				crc_16 ^= (qwe->c) << 8;
				for (j = 0; j < 8; j++) {
					if (crc_16 >= 32768) {
						crc_16 = crc_16 << 1;
						crc_16 = crc_16 ^ POLY;
					}
					else {
						crc_16 = crc_16 << 1;
					}
				}

				qwe = qwe->next;
			}
			wchar_t cim_crc = crc_16;
			if (cim_crc == 0) {
				cim_crc = '0';
			}
			unsigned short* crc_16_2;
			crc_16_2 = (unsigned short*)calloc(16, sizeof(unsigned short));
			printf("Dec: %d, Hex: %0x, Sym: %c, ", crc_16, crc_16, cim_crc);
			if (crc_16_2 != NULL) {
				for (i = 15; i >= 0; i--) {
					crc_16_2[i] = crc_16 % 2;
					crc_16 /= 2;
				}

				printf(" Bin: ");
				for (i = 0; i < 7; i++) {
					printf("%d", crc_16_2[i]);
				}
			}
		}
	}
	fclose(original_file);
	return 0;
}

// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "op_utils.h"

void write_ascii(info_image *pic, FILE *write)
{
	for (int i = 0; i < pic->row; ++i) {
		for (int j = 0; j < pic->column; ++j) {
			if (pic->type != 3) {
				fprintf(write, "%d ", (int)round(pic->image[i][j].red));
			} else {
				fprintf(write, "%d ", (int)round(pic->image[i][j].red));
				fprintf(write, "%d ", (int)round(pic->image[i][j].green));
				fprintf(write, "%d ", (int)round(pic->image[i][j].blue));
			}
		}
		fprintf(write, "\n");
	}
}

void write_binary(info_image *pic, FILE *write)
{
	for (int i = 0; i < pic->row; ++i)
		for (int j = 0; j < pic->column; ++j) {
			if (pic->type != 6) {
				char value = (char)round(pic->image[i][j].red);
				fwrite(&value, sizeof(char), 1, write);
			} else {
				char r, g, b;
				r = (char)round(pic->image[i][j].red);
				g = (char)round(pic->image[i][j].green);
				b = (char)round(pic->image[i][j].blue);
				fwrite(&r, sizeof(char), 1, write);
				fwrite(&g, sizeof(char), 1, write);
				fwrite(&b, sizeof(char), 1, write);
			}
		}
}

int save(char *input, info_image *pic)
{
	if (!pic->image) {
		printf("No image loaded\n");
		return 0;
	}
	// reading the file's name from the input
	char file_name[LENGTH], tmp[LENGTH];
	if (sscanf(input, "%s", file_name) == EOF) {
		fprintf(stderr, "sscanf() failed\n");
		return 0;
	}

	// we're getting rid of the file's name as it is stored in a different
	// string and we don't need to have it in input anymore
	strcpy(tmp, input + strlen(file_name));
	strcpy(input, tmp);

	// is_text is going to tell if we have to save the image in a text format
	char is_text[LENGTH] = "/n";
	if (strlen(input) > 4)
		// reading it with sscanf from the input string too
		if (sscanf(input, "%s", is_text) == EOF) {
			fprintf(stderr, "sscanf() failed\n");
			return 0;
		}

	// opening the file in binary format as we can write stuff in it using both
	// fprintf and fwrite
	FILE *write = fopen(file_name, "wb");
	if (!write) {
		fprintf(stderr, "failed to open\n");
		return 0;
	}

	if (!strcmp(is_text, "ascii")) {
		if (pic->type > 3)
			pic->type -= 3;// the pic's type is now specific to a text file

		fprintf(write, "P%d\n%d %d\n", pic->type, pic->column, pic->row);

		if (pic->type != 1)
			fprintf(write, "%d\n", pic->max);

		write_ascii(pic, write);
	} else {
		if (pic->type <= 3)
			pic->type += 3;// the pic's type is now specific to a binary file

		fprintf(write, "P%d\n%d %d\n", pic->type, pic->column, pic->row);

		if (pic->type != 4)
			fprintf(write, "%d\n", pic->max);

		write_binary(pic, write);
	}
	fclose(write);
	printf("Saved %s\n", file_name);
	return 1;
}

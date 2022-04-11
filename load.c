// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op_utils.h"
#include "alloc_utils.h"

void garbage(FILE *f)
{
	char comment, tmp[LENGTH];
	fscanf(f, "%c", &comment);
	if (comment == '#')
		fgets(tmp, LENGTH, f);
	else
		fseek(f, -1, SEEK_CUR);
}

void read_image(info_image *pic, FILE *read)
{
	if (pic->type <= 3)
		for (int i = 0; i < pic->row; ++i)
			for (int j = 0; j < pic->column; ++j)
				if (pic->type != 3) {
					unsigned char value;
					fscanf(read, "%hhu", &value);
					pic->image[i][j].red = value;
					pic->image[i][j].blue = value;
					pic->image[i][j].green = value;
				} else {
					unsigned char r, g, b;
					fscanf(read, "%hhu", &r);
					fscanf(read, "%hhu", &g);
					fscanf(read, "%hhu", &b);
					pic->image[i][j].red = r;
					pic->image[i][j].blue = b;
					pic->image[i][j].green = g;
				}
	else
		for (int i = 0; i < pic->row; ++i)
			for (int j = 0; j < pic->column; ++j)
				if (pic->type != 6) {
					unsigned char value;
					fread(&value, sizeof(unsigned char), 1, read);
					pic->image[i][j].red = value;
					pic->image[i][j].blue = value;
					pic->image[i][j].green = value;
				} else {
					unsigned char r, g, b;
					fread(&r, sizeof(unsigned char), 1, read);
					fread(&g, sizeof(unsigned char), 1, read);
					fread(&b, sizeof(unsigned char), 1, read);
					pic->image[i][j].red = r;
					pic->image[i][j].blue = b;
					pic->image[i][j].green = g;
				}
}

int load(char *input, info_image *pic)
{
	// finding the file name from the remaining input,
	// since "LOADED" was cropped
	char file_name[LENGTH];
	strcpy(file_name, strtok(input, "\n"));

	FILE *read = fopen(file_name, "rb");
	if (!read) {
		printf("Failed to load %s\n", file_name);
		free_matrix(pic->row, pic->image);
		pic->image = NULL;

		return 0; // failed to open error
	}
	// if there's already a matrix stored, we deallocate its space
	// awaiting for the new matrix
	if (pic->image)
		free_matrix(pic->row, pic->image);

	// we ignore the lines that contain comments
	garbage(read);

	// determining the type of image
	char image_type[3];
	fscanf(read, "%s", image_type);
	pic->type = image_type[1] - '0';

	garbage(read);

	// reading the length and the width of the picture
	fscanf(read, "%d %d\n", &pic->column, &pic->row);
	garbage(read);

	// if the picture is not black & white, we read its biggest
	// intensity of colour
	if (pic->type != 1 && pic->type != 4)
		fscanf(read, "%hhu\n", &pic->max);

	garbage(read);

	pic->image = alloc_matrix(pic->row, pic->column);
	if (!pic->image) {
		fprintf(stderr, "malloc() failed\n");
		return -1; // allocation error
	}
	read_image(pic, read);
	fclose(read);

	// the picture is fully selected
	pic->x1 = 0;
	pic->y1 = 0;
	pic->x2 = pic->column;
	pic->y2 = pic->row;
	printf("Loaded %s\n", file_name);
	return 1; // success
}

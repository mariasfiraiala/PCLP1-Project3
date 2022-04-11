// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op_utils.h"
#include "alloc_utils.h"

int rotate_clockwise(info_image *pic, int ok)
{
	rgb **tmp = alloc_matrix(pic->x2 - pic->x1, pic->y2 - pic->y1);
	if (!tmp) {
		fprintf(stderr, "malloc() failed\n");
		return -1;
	}

	// tmp only contains the values that need to be rotated
	for (int i = 0; i < pic->x2 - pic->x1; ++i)
		for (int j = 0; j < pic->y2 - pic->y1; ++j)
			tmp[i][j] = pic->image[pic->y2 - j - 1][pic->x1 + i];

	// when the selection is not the whole image, we need to find the initial
	// matrix in terms of tmp
	if (!ok) {
		for (int i = 0; i < pic->x2 - pic->x1; ++i)
			for (int j = 0; j < pic->y2 - pic->y1; ++j)
				pic->image[pic->y1 + i][pic->x1 + j] = tmp[i][j];
	} else {
		// when the image is fully selected, we need to make space for the
		// result by interchanging the number of rows with the number of
		// columns
		free_matrix(pic->row, pic->image);

		pic->image = alloc_matrix(pic->column, pic->row);
		if (!pic->image) {
			fprintf(stderr, "malloc() failed\n");
			return -1;
		}

		for (int i = 0; i < pic->column; ++i)
			for (int j = 0; j < pic->row; ++j)
				pic->image[i][j] = tmp[i][j];
	}
	// deallocating the now unnecessary tmp
	free_matrix(pic->x2 - pic->x1, tmp);
	return 1;
}

int rotate(char *input, info_image *pic)
{
	if (!pic->image) {
		printf("No image loaded\n");
		return 0;
	}

	// if we don't have only one value, then we print the error message
	if (wrong_input(input) != 1) {
	    printf("Invalid command\n");
	    return 0;
	}

	int angle, value[9] = {-360, -270, -180, -90, 0, 90, 180, 270, 360};
	if (sscanf(input, "%d", &angle) == EOF) {
		fprintf(stderr, "sscanf() failed\n");
		return 0;
	}

	// checking whether the angle is valid
	int i = 0;
	while (i < 9 && angle != value[i])
		++i;

	if (i == 9) {
		printf("Unsupported rotation angle\n");
		return 0;
	}

	// when the angle is 0, 360 or -360 we don't have to rotate the picture
	if (angle == 360 || angle == -360 || angle == 0) {
		printf("Rotated %d\n", angle);
		return 1;
	}

	angle += 360;
	int mem_ups;

	// when the matrix is fully selected
	if (pic->y2 - pic->y1 == pic->row && pic->x2 - pic->x1 == pic->column) {
		for (int i = 0; i < angle / 90; ++i) {
			mem_ups = rotate_clockwise(pic, 1);
			if (mem_ups == -1)
				return -1;

			// we set the new dimensions at every step of the rotation
			pic->row = pic->x2 - pic->x1;
			pic->column = pic->y2 - pic->y1;
			pic->x1 = 0;
			pic->y1 = 0;
			pic->x2 = pic->column;
			pic->y2 = pic->row;
		}

		printf("Rotated %d\n", angle - 360);
		return 1;
	}

	// when the selection isn't square and the matrix isn't fully selected:
	if (pic->x2 - pic->x1 != pic->y2 - pic->y1) {
		printf("The selection must be square\n");
		return 0;
	}

	// the rotation algorithm for when the selection is square
	for (int i = 0; i < angle / 90; ++i)
		mem_ups = rotate_clockwise(pic, 0);

	// memory allocation errors
	if (mem_ups == -1)
		return -1;

	printf("Rotated %d\n", angle - 360);
	return 1;
}

// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc_utils.h"
#include "op_utils.h"

int crop(info_image *pic)
{
	// error message for when there isn't any image loaded
	if (!pic->image) {
		printf("No image loaded\n");
		return 0;
	}

	rgb * *tmp = alloc_matrix(pic->y2 - pic->y1, pic->x2 - pic->x1);
	if (!tmp) {
		fprintf(stderr, "malloc() failed\n");
		return -1;
	}

	// rotation algorithm: we store the result in a temporary matrix
	for (int i = pic->y1; i < pic->y2; ++i)
		for (int j = pic->x1; j < pic->x2; ++j)
			tmp[i - pic->y1][j - pic->x1] = pic->image[i][j];

	// freeing the initial image
	free_matrix(pic->row, pic->image);
	// allocating space for the new, cropped image
	pic->image = alloc_matrix(pic->y2 - pic->y1, pic->x2 - pic->x1);
	if (!pic->image) {
		fprintf(stderr, "malloc() failed\n");
		return -1;
	}

	// putting the result back into the structure
	for (int i = 0; i < pic->y2 - pic->y1; ++i)
		for (int j = 0; j < pic->x2 - pic->x1; ++j)
			pic->image[i][j] = tmp[i][j];

	// we also free the auxiliary matrix
	free_matrix(pic->y2 - pic->y1, tmp);

	// setting the new size
	pic->row = pic->y2 - pic->y1;
	pic->column = pic->x2 - pic->x1;
	pic->x1 = 0;
	pic->y1 = 0;
	pic->x2 = pic->column;
	pic->y2 = pic->row;

	printf("Image cropped\n");
	return 1;
}

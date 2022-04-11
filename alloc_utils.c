// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include "alloc_utils.h"

// dynamically allocates memory for a matrix (int **)
//in other words we allocate memory for n pointers (arrays)
rgb **alloc_matrix(int row, int column)
{
	rgb **matrix = (rgb **)malloc(row * sizeof(rgb *));

	if (!matrix) {
		fprintf(stderr, "malloc() failed\n");
		return NULL;
	}
	//row allocation
	for (int i = 0; i < row; ++i) {
		//for each row we allocate column * sizeof(int)
		matrix[i] = (rgb *)malloc(column * sizeof(rgb));

		if (!matrix[i]) {
			fprintf(stderr, "malloc() failed\n");

			//for each row previously allocated, we deallocate since
			//the malloc() function failed
			while (--i >= 0)
				free(matrix[i]);

			free(matrix);
			return NULL;
		}
	}

	return matrix;
}

void free_matrix(int row, rgb **matrix)
{
	for (int i = 0; i < row; ++i)
		free(matrix[i]);
	free(matrix);
}

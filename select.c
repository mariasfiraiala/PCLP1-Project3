// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "op_utils.h"

void swap_int(int *a, int *b)
{
	if (*a > *b) {
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

int select_file(char *input, info_image *pic)
{
	if (!pic->image) {
		printf("No image loaded\n");
		return 0;
	}

	// checking if the SELECT operation has the specifier ALL
	if (strstr(input, "ALL")) {
		char tmp[LENGTH];
		if (sscanf(input, "%s", tmp) != EOF) {
			pic->x1 = 0;
			pic->x2 = pic->column;
			pic->y1 = 0;
			pic->y2 = pic->row;
			printf("Selected ALL\n");
			return 1;
		}
		printf("Invalid command\n");
		return 0;
	}

	// if there aren't 4 numbers, there is an invalid command
	if (wrong_input(input) != 4) {
		printf("Invalid command\n");
		return 0;
	}

	// reading the selection numbers
	int x, y, z, t;
	if (sscanf(input, "%d %d %d %d", &x, &y, &z, &t) == EOF) {
		fprintf(stderr, "sscanf() failed\n");
		return 0;
	}
	// for each pair (x1, x2), (y1, y2) we determine the minimum
	swap_int(&x, &z);
	swap_int(&y, &t);

	// checking whether the coordinates are valid
	if (x < 0 || y < 0 || z > pic->column || t > pic->row || x == z || y == t) {
		printf("Invalid set of coordinates\n");
		return 0;
	}

	// saving the final coordinates in the structure
	pic->x1 = x;
	pic->y1 = y;
	pic->x2 = z;
	pic->y2 = t;
	printf("Selected %d %d %d %d\n", x, y, z, t);
	return 1;
}

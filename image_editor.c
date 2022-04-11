// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_utils.h"

int main(void)
{
	char operation[LENGTH] = "", input[LENGTH] = "", tmp[LENGTH];
	info_image pic;
	int mem_ups;

	pic.image = NULL;
	pic.row = 0;
	pic.column = 0;
	pic.x1 = 0;
	pic.x2 = 0;
	pic.y1 = 0;
	pic.y2 = 0;

	// we execute operations as long as we aren't specifically told to stop
	// using the EXIT command
	do {
		// reading from stdin line by line
		fgets(input, LENGTH, stdin);
		// in case the row is simply empty we print the error message
		if (!strcmp(input, "\n"))
			strcpy(input, "garbage\n");

		// we need to determine the operation keyword from the entire input
		find_op(input, tmp);
		strcpy(operation, tmp);

		// in case we find problems allocating space we use mem_ups as a guard
		mem_ups = apply_op(operation, input, &pic);

		if (mem_ups == -1)
			return -1;

	} while (strcmp(operation, "EXIT"));

	return 0;
}

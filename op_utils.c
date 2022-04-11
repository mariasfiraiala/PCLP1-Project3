// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load.h"
#include "select.h"
#include "crop.h"
#include "rotate.h"
#include "apply.h"
#include "save.h"
#include "exit.h"

void find_op(char *input, char *task)
{
	char tmp[LENGTH];

	// we store the name of the operation in task
	strcpy(tmp, input);
	strcpy(task, strtok(tmp, "\n "));

	// we crop the name of the operation from the input
	strcpy(tmp, input + strlen(task) + 1);
	strcpy(input, tmp);
}

int apply_op(char *operation, char *input, info_image *pic)
{
	if (!strcmp(operation, "LOAD"))
		return load(input, pic);

	if (!strcmp(operation, "SELECT"))
		return select_file(input, pic);

	if (!strcmp(operation, "ROTATE"))
		return rotate(input, pic);

	if (!strcmp(operation, "CROP"))
		return crop(pic);

	if (!strcmp(operation, "APPLY"))
		return apply(input, pic);

	if (!strcmp(operation, "SAVE"))
		return save(input, pic);

	if (!strcmp(operation, "EXIT"))
		return exit_programme(pic);

	printf("Invalid command\n");
	return 0;
}

int wrong_input(char *input)
{
	int no_arg = 0;
	for (int i = 0 ; i < (int)strlen(input) - 1; ++i) {
		if (!strchr(" -", input[i])  && !isdigit(input[i])) {
			return 0;
		} else if (input[i] == '-' && !isdigit(input[i + 1])) {
			return 0;
		} else if (isdigit(input[i])) {
			++no_arg;
			int j = i;
			while (j < (int)strlen(input) && isdigit(input[j]))
				++j;
			i = j - 1;
		}
	}
	return no_arg;
}

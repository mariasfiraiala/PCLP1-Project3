// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "op_utils.h"
#include "alloc_utils.h"

int exit_programme(info_image *pic)
{
	if (!pic->image) {
		printf("No image loaded\n");
		return 0;
	}
	free_matrix(pic->row, pic->image);
	return 1;
}

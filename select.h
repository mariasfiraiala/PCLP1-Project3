// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __SELECT__
#define __SELECT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "op_utils.h"

/*
* @brief -> determines the minimum from 2 values and swaps them accordingly
* @param -> *a, *b = the values
* @return -> none
*/
void swap_int(int *a, int *b);

/*
* @brief -> the driver programme for the APPLY operation
* @param -> *input = what's left after we crop the operation name from the line
* @param -> *pic = stores info about the image + its matrix
* return -> 1 for success, 0 for failure
*/
int select_file(char *input, info_image *pic);

#endif

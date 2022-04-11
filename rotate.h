// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __ROTATE__
#define __ROTATE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op_utils.h"
#include "alloc_utils.h"

/*
* @brief -> rotates the image at 90 degrees depending on the ok value
* @param -> *pic = stores info about the image + its matrix
* @param -> ok = 1 for a fully selected image, 0 for a square selection
*            based on ok we apply the rotation algorithm
* @return -> 1 for success, -1 for allocation error
*/
int rotate_clockwise(info_image * pic, int ok);

/*
* @brief -> the driver programme for the ROTATE operation
* @param -> *input = what's left after we crop the operation name from the line
* @param -> *pic = stores info about the image + its matrix
* return -> 1 for success, 0 for failure, -1 for allocation error
*/
int rotate(char *input, info_image *pic);

#endif

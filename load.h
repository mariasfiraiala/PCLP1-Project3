// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __LOAD__
#define __LOAD__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op_utils.h"
#include "alloc_utils.h"
#include "load.h"

/*
* @brief -> reads a line full of comments
* @param -> *f = the file from which we read the line
* @return -> none
*/
void garbage(FILE * f);

/*
* @brief -> reads the matrix from either a text or a binary file
* @param -> *pic = stores info about the image + its matrix
* @param -> *read = the file from which we read the info
* @return -> none
*/
void read_image(info_image *pic, FILE *read);

/*
* @brief -> reads the image and its info and stores it
* @param -> *input = what's left after we get rid of the operation name
* @param -> *pic = stores info about the image + its matrix
* @return -> 1 for success, 0 for failure, -1 for allocation error
*/
int load(char *input, info_image *pic);

#endif

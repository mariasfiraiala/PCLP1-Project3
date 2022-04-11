// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __ALLOC_UTILS__
#define __ALLOC_UTILS__

#include <stdio.h>
#include <stdlib.h>
#include "op_utils.h"

/*
* @brief -> we allocate space for a matrix that has 3 pixels
* @param -> row = the number of rows the new matrix will have
* @param -> column = the number of columns the new matrix will have
* @return -> pointer to the newly allocated matrix
*/
rgb * *alloc_matrix(int row, int column);

/*
* @brief -> frees a matrix with 3 fields for each element
* @param -> row = the number of rows
* @param -> **matrix = the matrix that needs to be deallocated
* @return -> none
*/
void free_matrix(int row, rgb **matrix);

#endif

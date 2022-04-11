// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __APPLY__
#define __APPLY__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op_utils.h"
#include "alloc_utils.h"

/*
* @brief -> restricts the value to a given range ([0, 255])
* @param -> n = the value that needs to be restricted
* @param -> min = the minimum value permited
* @param -> max = the maximum value permited
* @return -> returns the changed number
*/
double clamp(double n, int min, int max);

/*
* @brief -> can apply any filter given by the kernel matrix
* @param -> *pic = stores info about the image + its matrix
* @param -> kernel[][3] = the kernel matrix used to apply the  filter
* @param -> divide = the number used to divide the kernels with float numbers
* @return -> 1 for success, -1 for allocation error
*/
int apply_any_filter(info_image *pic, int kernel[][3], int divide);

/*
* @brief -> applies the edge filter
* @param -> *pic = stores info about the image + its matrix
* @return -> 1 for success, 0 for failure, -1 for allocation error
*/
int apply_edge(info_image *pic);

/*
* @brief -> applies the sharpen filter
* @param -> *pic = stores info about the image + its matrix
* @return -> 1 for success, 0 for failure, -1 for allocation error
*/
int apply_sharpen(info_image *pic);

/*
* @brief -> applies the box blur filter
* @param -> *pic = stores info about the image + its matrix
* @return -> 1 for success, 0 for failure, -1 for allocation error
*/
int apply_blur(info_image *pic);

/*
* @brief -> applies the gaussian blur filter
* @param -> *pic = stores info about the image + its matrix
* @return -> 1 for success, 0 for failure, -1 for allocation error
*/
int apply_gaussian(info_image *pic);

/*
* @brief -> the driver programme for the APPLY operation
* @param -> *input = what's left after we crop the operation name from the line
* @param -> *pic = stores info about the image + its matrix
* return -> 1 for success, 0 for failure, -1 for allocation error
*/
int apply(char *input, info_image *pic);

#endif

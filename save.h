// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __SAVE__
#define __SAVE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op_utils.h"

/*
* @brief -> writes the image matrix into a text file
* @param -> *pic = stores info about the image + its matrix
* @param -> *write = the file in which we write the info
* @return -> none
*/
void write_ascii(info_image * pic, FILE * write);

/*
* @brief -> writes the image matrix into a binary file
* @param -> *pic = stores info about the image + its matrix
* @param -> *write = the file in which we write the info
* @return -> none
*/
void write_binary(info_image *pic, FILE *write);

/*
* @brief -> saves the image and its info in a text or binary format
* @param -> *input = what's left after we get rid of the operation name
* @param -> *pic = stores info about the image + its matrix
* @return -> 1 for success, 0 for failure
*/
int save(char *input, info_image *pic);

#endif

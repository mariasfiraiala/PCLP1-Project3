// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __CROP__
#define __CROP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc_utils.h"
#include "op_utils.h"

/*
* @brief -> cropes the image based off the selected area
* @param -> *pic = stores info about the image + its matrix
* @return -> 1 for success, 0 for failure, -1 for allocation error
*/
int crop(info_image * pic);

#endif

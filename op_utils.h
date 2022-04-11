// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#ifndef __OP_UTILS__
#define __OP_UTILS__

#define LENGTH 1000

typedef struct {
	double red, blue, green;
} rgb;

typedef struct {
	int row, column;
	int x1, y1, x2, y2;
	int type;
	unsigned char max;

	rgb **image;
} info_image;

/*
* @brief -> we determine whether a string contains only numbers
* @param -> *input = the string we want to check
* @return -> 0, when the string doesn't contain any numbers, otherwise
*			 the number of numbers
*/
int wrong_input(char *input);

/*
* @brief -> we determine the task from an entire line of input
* @param -> *input = the entire line from which we extract
* @param -> **task = memorizes the task
* @return -> we don't return anything as we directly modify both input and task
*/
void find_op(char *input, char *task);

/*
* @brief -> executes each task
* @param -> *operation = the task
* @param -> *input = the rest of the input (unique variables to each command)
* @param -> pic = an entire set of information regarding the stored image
* @return -> the value varies but, -1 always means allocation error
*/
int apply_op(char *operation, char *input, info_image *pic);

#endif

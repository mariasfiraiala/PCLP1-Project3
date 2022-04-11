// Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_utils.h"
#include "alloc_utils.h"

double clamp(double n, int min, int max)
{
	if (n < min)
		n = min;
	else if (n > max)
		n = max;
	return n;
}

int apply_any_filter(info_image *pic, int kernel[][3], int divide)
{
	rgb **tmp = alloc_matrix(pic->row, pic->column);
	if (!tmp) {
		fprintf(stderr, "malloc() failed\n");
		return -1;// returning -1 for memory allocation failure
	}

	// if the selection contains one of the first/last rows or one of the
	// first/last columns, these elements shouldn't be affected by the APPLY
	int first_i = pic->y1, first_j = pic->x1;
	int last_i = pic->y2, last_j = pic->x2;
	if (pic->x1 == 0)
		++first_j;
	if (pic->y1 == 0)
		++first_i;
	if (pic->x2 == pic->column)
		--last_j;
	if (pic->y2 == pic->row)
		--last_i;

	for (int i = first_i; i < last_i; ++i)
		for (int j = first_j; j < last_j; ++j) {
			double sumr = 0., sumb = 0., sumg = 0.;

			// moving through both the kernel matrix and the original image
			// matrix
			for (int m = 0; m < 3; ++m) {
				for (int n = 0; n < 3; ++n) {
					// we apply the kernel for every pixel
					sumr += pic->image[i + m - 1][j + n - 1].red *
							kernel[m][n];
					sumb += pic->image[i + m - 1][j + n - 1].blue *
							kernel[m][n];
					sumg += pic->image[i + m - 1][j + n - 1].green *
							kernel[m][n];
				}
			}
			// finally, we apply the clamp function too, in order avoid an
			// overflow
			tmp[i][j].red = clamp((double)sumr / divide, 0, 255);
			tmp[i][j].blue = clamp((double)sumb / divide, 0, 255);
			tmp[i][j].green = clamp((double)sumg / divide, 0, 255);
		}

	// transfering the result to the original image
	for (int i = first_i; i < last_i; ++i)
		for (int j = first_j; j < last_j; ++j)
			pic->image[i][j] = tmp[i][j];

	// we free the auxiliary matrix
	free_matrix(pic->row, tmp);

	return 1;// returning 1 for success
}

int error_message(info_image *pic)
{
	// if the picture is black & white or grayscale, we cannot perform APPLY
	if (pic->type != 3 && pic->type != 6) {
		printf("Easy, Charlie Chaplin\n");
		return 0;
	}
	return 1;
}

int apply_edge(info_image *pic)
{
	// the kernel matrix specific to the edge filter
	int edge_kernel[3][3] = {{-1, -1, -1}, {-1, 8, -1,}, {-1, -1, -1}};

	if (!error_message(pic))
		return 0;

	if (apply_any_filter(pic, edge_kernel, 1) != -1) {
		printf("APPLY EDGE done\n");
		return 1;
	}
	return -1;
}

int apply_sharpen(info_image *pic)
{
	// the kernel matrix specific to the sharpen filter
	int sharpen_kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

	if (!error_message(pic))
		return 0;

	if (apply_any_filter(pic, sharpen_kernel, 1) != -1) {
		printf("APPLY SHARPEN done\n");
		return 1;
	}
	return -1;
}

int apply_blur(info_image *pic)
{
	// the kernel matrix specific to the box blur filter
	// + divide = 9 for substracting
	int blur_kernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

	if (!error_message(pic))
		return 0;

	if (apply_any_filter(pic, blur_kernel, 9) != -1) {
		printf("APPLY BLUR done\n");
		return 1;
	}
	return -1;
}

int apply_gaussian(info_image *pic)
{
	// the kernel matrix specific to the box blur filter
	// + divide = 16 for substracting
	int gaussian_kernel[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

	if (!error_message(pic))
		return 0;

	if (apply_any_filter(pic, gaussian_kernel, 16) != -1) {
		printf("APPLY GAUSSIAN_BLUR done\n");
		return 1;
	}
	return -1;
}

int apply(char *input, info_image *pic)
{
	// when there isn't anything to apply the filter on
	// we print the error message
	if (!pic->image) {
		printf("No image loaded\n");
		return 0;
	}

	// char parameter[LENGTH];
	// strcpy(parameter, strtok(input, "\n "));
	char parameter[LENGTH];
	// when APPLY doesn't have a parameter, the command is invalid
	if (sscanf(input, "%s", parameter) == EOF) {
		printf("Invalid command\n");
		return 0;
	}

	if (!strcmp(parameter, "EDGE"))
		return apply_edge(pic);
	if (!strcmp(parameter, "SHARPEN"))
		return apply_sharpen(pic);
	if (!strcmp(parameter, "BLUR"))
		return apply_blur(pic);
	if (!strcmp(parameter, "GAUSSIAN_BLUR"))
		return apply_gaussian(pic);

	printf("APPLY parameter invalid\n");
	return 0;
}

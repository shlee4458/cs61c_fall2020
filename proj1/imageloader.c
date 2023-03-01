/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp;
	int total_pixels;  int max_pixel;

	/* Open file as a read only mode */
	fp = fopen(filename, "r");

	/* Check the format */
	char c[3];
	fscanf(fp, "%s", c);
	if (c[0] != 'P' || c[1] != '3') {
		printf("This is not a PPM file!");
		return NULL;
	}

	/* Initiate an Image instance */
	Image *img = (Image *) malloc(sizeof(Image));

	/* Get row, col and max_pixel value from the file */
	fscanf(fp, "%u %u %d", &img->cols, &img->rows, &max_pixel);
	total_pixels = img->cols * img->rows;
	if (max_pixel != 255) {
		printf("Max Pixel is not correct!");
		return NULL;
	}
	
	/* Initiate Color Array */
	Color **color = (Color **) malloc(sizeof(Color *) * total_pixels);
	img->image = color;

	/* Iterate over rows and cols to get r, g, b values and assign it to the Color instances */

	for (int i = 0; i < total_pixels; i++) {
			/* Initiate Color instance */
			color[i] = (Color *) malloc(sizeof(Color));
			Color *pixel = color[i];
			
			/* Read R, G, B from the file */
			fscanf(fp, "%hhu %hhu %hhu", &pixel->R, &pixel->G, &pixel->B);
			
			/* Assign R, G, B values */
			// pixel->R = R;
			// pixel->G = G;
			// pixel->B = B;
	}

	/* Close the file */
	fclose(fp);
	
	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE	
	uint32_t row;  uint32_t col;
	row = image->rows;
	col = image->cols;
	Color **color = image->image;

	printf("P3\n%d %d\n255\n", col, row);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col - 1; c++) {
			printf("%3hhu %3hhu %3hhu   ", (*color)->R, (*color)->G, (*color)->B);
			color++;
		}
		printf("%3hhu %3hhu %3hhu\n", (*color)->R, (*color)->G, (*color)->B);
		color++;
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	int total_pixels = image->rows * image->cols;

	/* Free individual color instance -> array of colors -> Image */
	for (int i = 0; i < total_pixels; i++) {
		free(image->image[i]);
	}

	free(image->image);
	free(image);
}
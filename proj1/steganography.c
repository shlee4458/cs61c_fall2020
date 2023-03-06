/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	int idx = row * image->cols + col; // find the index of the color
	Color *newColor = (Color *) malloc(sizeof(Color)); // create a memory for the color

	/* Get Color from the image at idx and assign it into the Color instance */
	newColor = image->image[idx];
	int b_bin = (newColor->B) & 1; // get the LSB value of the B channel in the color
	newColor->R = b_bin * 255;
	newColor->G = b_bin * 255;
	newColor->B = b_bin * 255;

	/* Return the color */
	return newColor;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	int ROW = image->rows;
	int COL = image->cols;
	int idx;

	/* Create a new memory for image */
	Image *steg_image = (Image *) malloc(sizeof(Image));
	steg_image->rows = ROW;
	steg_image->cols = COL;
	steg_image->image = (Color **) malloc(sizeof(Color *) * ROW * COL);

	/* Loop over all the grid in the image and get the Color instance in each grid */
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			idx = r * COL + c; // Find index of the array
			steg_image->image[idx] = evaluateOnePixel(image, r, c); // Assign that into the newly Created image
		}
	}

	return steg_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 2) {
		printf("%s", argv[0]);
		return -1;
	}

	Image *image = readData(argv[1]); // load the file to the image struct
	Image *steg_image = steganography(image); // decode the loaded image
	writeData(steg_image); // print the image 
	free(image); 
	free(steg_image);
}

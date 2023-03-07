/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
// Note that you will need to read the eight neighbors of the cell in question. 
// The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	/* Get the number of cells alive in the 8 directions */
	int ROW = image->rows;
	int COL = image->cols;
	int isAliveR, isAliveG, isAliveB; // whether R, G, B is 255 for the current cell
	int numAliveR, numAliveG, numAliveB = 0; // number of cells alive for each channel
	int idx = row * COL + col; // index of the current cell

	/* Check if R, G, B value of the given cell is alive */
	isAliveR = (image->image[idx]->R == 255);
	isAliveG = (image->image[idx]->G == 255);
	isAliveB = (image->image[idx]->B == 255);

	for (int r = -1 + row; r <= 1 + row; r++) {
		for (int c = -1 + col; c <= 1 + col; c++) {
			if (r != row && c != col) {
				int wrap_r = r % ROW; // wrap the index
				int wrap_c = c % COL;

				if (image->image[wrap_r * COL + wrap_c]->R == 255) { // if the R cell is alive
					numAliveR += 1; // add one to alive
				}

				if (image->image[wrap_r * COL + wrap_c]->G == 255) { // if the R cell is alive
					numAliveG += 1; // add one to alive
				}

				if (image->image[wrap_r * COL + wrap_c]->B == 255) { // if the R cell is alive
					numAliveB += 1; // add one to alive
				}
			}
		}
	}

	/* Get the digit in the rule */
	// if the cell is alive, update number of shifts by 9 for each channel
	numAliveR = 9 * isAliveR + numAliveR;
	numAliveG = 9 * isAliveG + numAliveG;
	numAliveB = 9 * isAliveB + numAliveB;

	// using the number of cells alive, find the value from the rule
	int live_or_deadR = (rule & (1 << numAliveR)) >> numAliveR; // mask the alive_th digit of the rule
	int live_or_deadG = (rule & (1 << numAliveG)) >> numAliveG; // mask the alive_th digit of the rule
	int live_or_deadB = (rule & (1 << numAliveB)) >> numAliveB; // mask the alive_th digit of the rule

	// return the color with the value
	Color *color = (Color *) malloc(sizeof(Color)); // create a new memory
	color->R = live_or_deadR * 255;
	color->G = live_or_deadG * 255;
	color->B = live_or_deadB * 255;
	printf("%d %d\n", row, col);
	printf("%d\n", color->R);
	return color;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	
	/* Declare variables */
	int idx;
	int ROW = image->rows;
	int COL = image->cols;

	/* Create a new memory for return image */
	Image *life_image = (Image *) malloc(sizeof(Image));
	life_image->image = (Color **) malloc(sizeof(Color *) * ROW * COL);
	life_image->rows = ROW;
	life_image->cols = COL;

	/* Get the life of the given image by looping over all the grid in the image and 
	putting the Color instance in each grid */
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			idx = r * COL + c;
			life_image->image[idx] = evaluateOneCell(image, r, c, rule);
		}
	}

	return life_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) { // if number of arguments does not match return - 1
		printf("%s", argv[1]);
		return -1;
	}

	Image *image = readData(argv[1]); // read the image
	uint32_t rule = strtol(argv[2], NULL, 16);
	Image *life_image = life(image, rule); // convert to the lift image
	writeData(life_image); // Print the life image

	/* Free the memory */
	freeImage(image);
	freeImage(life_image);
}

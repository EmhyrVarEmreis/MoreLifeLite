/*
 * world.h
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef WORLD_H_
#define WORLD_H_

/**
 * The structure of main GRID called WORLD. The main concept is that
 *  every cell is represented as a number of small range ( char -> <256 ).
 *  The number is STATE+NUMBER_OF_NEIGHBORS, where STATE is MLL_CELL_DEAD
 *  for dead cells and MLL_CELL_ALIVE for alive cells. See mll_constants.h
 *  for detailed numbers.
 */
typedef struct {
		int x;		/* GRID WIDTH */
		int y;		/* GRID HEIGHT */
		int size;	/* GRID SIZE - useful for optimalization of grid processing functions */
		int* data;	/* DATA VALUES OF GRID */
} world;


/**
 * Makes initialization of WORLD (GRID).
 * @param x_size	GRID WIDTH
 * @param y_size	GRID HEIGHT
 * @return			POINTER TO GRID
 */
world*	world_init		( int x_size, int y_size );

/**
 * Resizes WORLD (GRID) to preffered size.
 * @param w			POINTER TO GRID
 * @param x_size	GRID WIDTH
 * @param y_size	GRID HEIGHT
 */
void	world_resize	( world* w, int x_size, int y_size );

/**
 * Clears WORLD (GRID).
 * @param w			POINTER TO WORLD (GRID)
 */
void	world_clear		( world* w );

/**
 * Frees memory containing WORLD (GRID).
 * @param w			POINTER TO WORLD (GRID)
 */
void	world_free		( world* w );

/**
 * Prints WORLD (GRID) to stdout.
 * @param w			POINTER TO WORLD (GRID)
 */
void	world_print		( world* w );

/**
 * Makes an initialized world filled with randomized content.
 * @param w			POINTER TO WORLD (GRID)
 */
void	world_randomize	( world* w );


#endif /* WORLD_H_ */

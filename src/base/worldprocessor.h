/*
 * worldprocessor.h
 *
 *  Created on: 26 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef WORLDPROCESSOR_H_
#define WORLDPROCESSOR_H_

#include "world.h"

/**
 * Makes one cycle of WORLD (GRID) life.
 * @param w			POINTER TO WORLD (GRID)
 * @param torus		0/1 OFF/ON TORUS MODE
 */
void	worldprocessor_make_cycle_simple				( world* w, int torus );

/**
 * Makes one cycle of WORLD (GRID) life but provides more options.
 * @param w			POINTER TO WORLD (GRID)
 * @param h			POINTER TO WORLD (GRID) TREATED AS HEAT MAP
 * @param torus		0/1 FALSE/TRUE  - MAKE TORUS OR NOT
 */
void	worldprocessor_make_cycle_full					( world* w, world* h, int torus  );

/**
 * Processes cells of WORLD (GRID) - calculates Moore's neighborhood and stores
 *  calculated data in WORLD (GRID). Data values of WORLD (GRID) after this process
 *  can be non-/hard to read or interpretate. Uses torus as methd to solve boundary
 *  conditions problems.
 * @param w			POINTER TO WORLD (GRID)
 */
void	worldprocessor_process_cells_torus				( world* w );

/**
 * Processes cells of WORLD (GRID) - calculates Moore's neighborhood and stores
 *  calculated data in WORLD (GRID). Data values of WORLD (GRID) after this process
 *  can be non-/hard to read or interpretate.
 * @param w			POINTER TO WORLD (GRID)
 */
void	worldprocessor_process_cells					( world* w );

/**
 * Post-processes cells of WORLD (GRID) - kills or revives cell depending
 *  on calculated Moore's neighborhood stored in WORLD (GRID). This function makes
 *  grid easy-readable, because converts data to only information about alive or dead cells.
 * @param w			POINTER TO WORLD (GRID)
 */
void	worldprocessor_post_process_cells				( world* w );

/**
 * Post-processes cells of WORLD (GRID) - kills or revives cell depending
 *  on calculated Moore's neighborhood stored in WORLD (GRID). This function makes
 *  grid easy-readable, because converts data to only information about alive or dead cells.
 *  Calculates and stores map of cell changes (called heat map).
 * @param w			POINTER TO WORLD (GRID)
 * @param h			POINTER TO WORLD (GRID) TREATED AS HEAT MAP
 */
void	worldprocessor_post_process_cells_with_heating	( world* w, world* h );

/**
 * Checks if a cell in WORLD (GRID) is dead or alive.
 * @param w			POINTER TO WORLD (GRID)
 * @param x_pos		"X" (BY WIDTH) POSITION OF CELL IN WORLD (GRID)
 * @param y_pos
 * @return			"0" IF DEAD or "1" IF ALIVE
 */
int		worldprocessor_is_cell_alive					( world* w, int x_pos, int y_pos );

/**
 * Counts and returns number of alive cells.
 * @param w			POINTER TO WORLD (GRID)
 * @return			NUMBER OF ALIVE CELLS
 */
int		worldprocessor_alive_cells_count				( world* w );

#endif /* WORLDPROCESSOR_H_ */

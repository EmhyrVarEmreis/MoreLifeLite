/*
 * mll_constants.h
 *
 *  Created on: 8 mar 2014
 *      Author: Mateusz Stefaniak
 * Description: This file contains main CONSTANTS of MoreLifeLite program.
 */

#ifndef MLL_CONSTANTS_H_
#define MLL_CONSTANTS_H_

/**
 * Dead cell data.
 */
#define MLL_CELL_DEAD 0

/**
 * Alive cell data.
 */
#define MLL_CELL_ALIVE 10

/**
 * "Border" cell data - above (>) this number cell can
 * 	be interpreted as alive cell and below (=<) as dead.
 */
#define MLL_CELL_BORDER 9

#endif /* MLL_CONSTANTS_H_ */

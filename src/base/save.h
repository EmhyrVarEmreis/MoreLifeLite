/*
 * save.h
 *
 *  Created on: 28 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef SAVE_H_
#define SAVE_H_

#include "world.h"

/**
 * Saves world grid as SVG image.
 * @param w				POINTER TO WORLD (GRID)
 * @param filename		PATH TO SAVE + FILE NAME
 * @param cycle			CYCLE NUMBER (NEGATIVE NUMBER TO NONE)
 * @param alive			ALIVE CELLS COUNT (NEGATIVE NUMBER TO NONE)
 * @return
 */
int		save_svg			( world* w, char* filename, int cycle, int alive);

/**
 * Saves world grid as PNG image.
 * @param w				POINTER TO WORLD (GRID)
 * @param filename		PATH TO SAVE + FILE NAME
 * @param cycle			CYCLE NUMBER
 * @param alive			ALIVE CELLS COUNT
 * @return
 */
int		save_png			( world* w, char* filename, int cycle, int alive);

/**
 * Saves heat map structure as SVG image.
 * @param w				POINTER TO WORLD (GRID) TREATED AS HEAT MAP
 * @param filename		PATH TO SAVE + FILE NAME
 * @return
 */
int		save_svg_hm			( world* w, char* filename );


/**
 * Saves heat map structure as PNG image.
 * @param w				POINTER TO WORLD (GRID) TREATED AS HEAT MAP
 * @param filename		PATH TO SAVE + FILE NAME
 * @return
 */
int		save_png_hm			( world* w, char* filename );

#endif /* SAVE_H_ */

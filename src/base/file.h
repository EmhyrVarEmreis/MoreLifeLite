/*
 * file.h
 *
 *  Created on: 26 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>

#include "world.h"
#include "structs.h"

/**
 * Reads WORLD (GRID) from file from file and store it in vaid structure.
 * @param w				POINTER TO WORLD (GRID)
 * @param filename		PATH TO FILE TO READ
 * @param s				STRUCTS TO PLACE ON GRID
 * @return				0 - FILE PROPERLY READED
 * 						1 - INCORRECT FILE EXTENSION (ONLY WARNING - READED PROPERLY)
 * 						10 - INCORRECT FILE FORMAT
 */
int		file_read_world			( world* w, char* filename, structs* s );

/**
 * Saves WORLD (GRID) in proper format.
 * @param w				POINTER TO WORLD (GRID)
 * @param filename		PATH TO FILE TO SAVE
 * @return				1 - FILE PROPERLY SAVED
 * 						0 - ERRORS OCCURED
 */
int		file_save_world			( world* w, char* filename, int cycle_number, int alive_cells );

/**
 * Makes initialization (opens) file to store stats for gnuplot.
 * @param filename		PATH TO FILE
 * @return				NULL OR POINTER TO FILE
 */
FILE*	file_stats_gnuplot_init	( char* filename );


/**
 * Writes record to file for gnuplot(-ing).
 * @param out			POINTER TO FILE
 * @param cycle_number	CYCLE NUMBER
 * @param alive_cells	ALIVE CELLS COUNT
 * @return				1 - RECORD PROPERLY SAVED
 * 						0 - ERRORS OCCURED
 */
int		file_stats_gnuplot_write( FILE* out, int cycle_number, int alive_cells );

#endif /* FILE_H_ */

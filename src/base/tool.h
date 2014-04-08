/*
 * tool.h
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef TOOL_H_
#define TOOL_H_

#include "options.h"
#include "world.h"

/**
 * Makes a full dump of current state. Saves PNG, TXT, SVG, gnuplot file depending on options.
 * @param o				POINTER TO OPTIONS STRUCTURE
 * @param w				POINTER TO WORLD (GRID) STRUCTURE
 * @param h				POINTER TO WORLD (GRID) TREATED AS HEAT MAP STRUCTURE
 * @param n				CYCLE NUMBER
 * @param dumps_num		DUMP NUMBER
 * @param buf			BUFOR FOR STRING OPERATIONS
 * @return				NEXT DUMP NUMBER
 */
void		tool_make_dump			( options* o, world* w, world* h, int n, int* dumps_num );

/**
 * Compares two strings limited to preffered size.
 * @param a				STRING A
 * @param b				STRING B
 * @param c				NUMBER OF CHARS TO COMPARE
 * @return				RESULT - 0/1 FALSE/TRUE
 */
int			tool_str_cmp			( char* a, char* b, int c );

/**
 * Sets world's size to params readed from string ( eg. "SOMETHING100x100").
 * @param w				POINTER TO WORLD (GRID) STRUCTURE
 * @param a				STRING WITH PREFFERED SIZE
 * @return				RESULT - 0/1 INCORRECTLY/PROPERLY
 */
int			tool_set_world_size		( world* w, char* a );

/**
 * Search a string in strings array.
 * @param n				ARRAY LENGTH
 * @param array			POINTER TO ARRAY
 * @param str			POINTER TO STRING TO SEARCH FOR
 * @return
 */
int			tool_search_string		( int n, char** array, char* str );

#endif /* TOOL_H_ */

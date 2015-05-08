/*
 * options.h
 *
 *  Created on: 28 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <stdio.h>

/**
 * Structure, which holds options
 */
typedef struct {
		int options[12];
		/*
		 * 0  - generate PNG images
		 * 1  - generate SVG images
		 * 2  - generate heat map
		 * 3  - generate statistics
		 * 4  - print states to stdout
		 * 5  - silent (no basic information to stdout) mode
		 * 6  - torus simulation
		 * 7  - generate TXT files
		 * 8  - number of cycles
		 * 9  - frequency of dumps
		 * 10 - generate gnuplot files
		 * 11 - show help
		 */
		char strings[8][256];
		/*
		 * 0 - path_gen
		 * 1 - file_to_read
		 * 2 - file_structs_to_read
		 * 3 - rules
		 * 4 - path_history
		 * 5 - path_png
		 * 6 - path_svg
		 * 7 - path_txt
		 */
		FILE* gnuplot; /* file for gnuplot stats */
} options;

/**
 * Makes initialization of options structure.
 * @return			POINTER TO OPTIONS
 */
options*	options_init			();

/**
 * Parses options.
 * @param o			POINTER TO OPTIONS
 * @param argc_a	ARGS COUNT
 * @param argv_a	ARGC ARRAY
 * @return			1/0 - OK / ERRORS OCCURED
 */
int			options_parse		( options* o, int argc_a, char** argv_a);

/**
 * Sets default options.
 * @param o			POINTER TO OPTIONS
 */
void		options_set_defaults		( options* o );

/**
 * Checks if help argument is set.
 * @param argc          ARRAY LENGTH
 * @param argv          POINTER TO ARRAY
 * @return		0 IF NOT SET; 1 IF SET
 */
int             options_check_help		( int argc, char** argv );

/**
 * Checks for unsetted arguments in aguments array for thoose
 *  which are required to lauch program properly.
 * @param argc		ARRAY LENGTH
 * @param argv		POINTER TO ARRAY
 * @return
 */
int		options_check_min		( int argc, char** argv );

/**
 * Frees memory.
 * @param o			POINTER TO OPTIONS
 */
void		options_free			( options* o);

#endif /* OPTIONS_H_ */

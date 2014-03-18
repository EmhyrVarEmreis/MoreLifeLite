/*
 * options.h
 *
 *  Created on: 28 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <stdio.h>

typedef struct {
		int options[12];
		/*
		 * 0  - ch_png_gen
		 * 1  - ch_svg_gen
		 * 2  - ch_history_heat_map_gen
		 * 3  - ch_statistic_gen
		 * 4  - ch_state_to_stdout
		 * 5  - silent_mode
		 * 6  - torus
		 * 7  - ch_txt_gen
		 * 8  - cycle_number
		 * 9  - frequency
		 * 10 - gnuplot_gen
		 * 11 - help_show
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
int			options_parse			( options* o, int argc_a, char** argv_a);

/**
 * Sets default options.
 * @param o			POINTER TO OPTIONS
 */
void		options_set_defaults	( options* o );

/**
 * Frees memory.
 * @param o			POINTER TO OPTIONS
 */
void		options_free			( options* o);

#endif /* OPTIONS_H_ */

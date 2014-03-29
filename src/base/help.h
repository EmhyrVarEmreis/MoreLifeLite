/*
 * help.h
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef HELP_H_
#define HELP_H_

#include "options.h"

/**
 * Shows ascii art with program logo.
 */
void help_ascii_art( );

/**
 * Shows full help.
 */
void help_show( );

/**
 * Ptints horizontal line.
 */
void help_print_line( );


/**
 * Prints options to stdout.
 * @param o		POINTER TO OPTIONS
 */
void help_print_options( options* o );

#endif /* HELP_H_ */

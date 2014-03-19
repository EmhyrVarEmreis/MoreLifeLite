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

void help_print_line( );

void help_print_options( options* o );

#endif /* HELP_H_ */

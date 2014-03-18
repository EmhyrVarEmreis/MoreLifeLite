/*
 * rules.h
 *
 *  Created on: 8 mar 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef RULES_H_
#define RULES_H_

#define RULES_SIZE 20

/**
 * Checks if the string that (maybe) contains rules is in valid format. For
 *  detailed information about its formatting see (but discard lettes B and S)
 *  http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Variations_on_Life
 *  An Example of properly formatted string is "23/3" and it represents rules
 *  presented by John Conway.
 * @param r			STRING WITH RULES
 * @return			"0" IF NOT or "1" IF OK
 */
int		rules_is_valid		( char* r );

/**
 * Sets simulator rules on those represented by string (see params below). For
 *  more inromation you can read maual or look at information about rules_is_valid
 *  function (probably somewhere in this file).
 * @param r
 */
void	rules_set			( char* r );

/**
 * Sets rules of this simulator on those presented by John Conway.
 */
void	rules_set_conway	(  );

/**
 * Returns proper new data value of cell depending on its current value. This
 *  function is used in the main processing function (see worldprocessor.c/.h).
 * @param c			CELL DATA VALUE
 * @return			NEW CELL DATA VALUE
 */
int	rules_process_cell	( int c );

/**
 * Prints rules on stdout in format "CELL_DATA_VALUE->NEW_CELL_DATA_VALUE\n".
 */
void	rules_print			();

/**
 * Clears rules by setting the rule as "always dead".
 */
void	rules_clear			();

#endif /* RULES_H_ */

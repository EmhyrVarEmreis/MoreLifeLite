/*
 * rules.c
 *
 *  Created on: 8 mar 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "rules.h"
#include "mll_constants.h"

static int rules[RULES_SIZE];

int rules_is_valid( char* r ) {
	while (*r) {
		if ( !(isdigit( *r ) || *r == '/') )
			return 0;
		r++;
	}
	return 1;
}

void rules_set( char* r ) {

	int a;

	rules_clear();

	/* Set alive mode */
	a = MLL_CELL_DEAD;

	/* Read from string */
	while (isdigit( *r ) || *r == '/') {
		/* Swith mode when '/' occures */
		if ( *r == '/' )
			a = -1;
		else
			rules[a + ((*r) - '0') + 1] = MLL_CELL_ALIVE;
		r++;
	}
}

void rules_set_conway() {
	rules_set( "23/3" );
}

int rules_process_cell( int c ) {
	/* Return proper state of cell depending on its current value */
	return rules[c];
}

void rules_print() {
	int a;
	for ( a = 0; a < RULES_SIZE; a++ )
		printf( "%d->%d\n", a, (int)rules[(int) a] );
}

void rules_clear() {
	int a;

	for ( a = 0; a < RULES_SIZE; a++ )
		rules[a] = MLL_CELL_DEAD;
}

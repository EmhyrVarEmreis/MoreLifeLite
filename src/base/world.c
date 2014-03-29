/*
 * world.c
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "world.h"
#include "mll_constants.h"

world* world_init( int x_size, int y_size ) {

	world * w;

	/* Allocate pointer */
	w = malloc( sizeof *w );

	/* Set size */
	w->x = x_size;
	w->y = y_size;
	w->size = w->x * w->y;

	/* Allocate memory for data */
	w->data = malloc( x_size * y_size * sizeof *(w->data) );

	/* Clear world - set all cells to dead state */
	world_clear( w );

	return w;
}

void world_resize( world* w, int x_size, int y_size ) {
	/* Set new size */
	w->x = x_size;
	w->y = y_size;
	w->size = w->x * w->y;

	/* Reallocate with new size */
	w->data = realloc( w->data, x_size * y_size * sizeof *(w->data) );
}

void world_clear( world* w ) {
	int i;
	for ( i = 0; i < w->size; i++ )
		w->data[i] = MLL_CELL_DEAD;
}

void world_free( world* w ) {
	if ( w != NULL ) {
		free( w->data );
		free( w );
	}
}

void world_print( world* w ) {
	int i, j;

	for ( i = 0; i < w->y; i++ ) {
		for ( j = 0; j < w->x; j++ ) {
			printf( "%c", (w->data[i * w->x + j] > MLL_CELL_BORDER ? 'A' : 'D') );
		}
		printf( "\n" );
	}
}

void world_randomize( world* w ) {
	int i;
	/* Init srand */
	srand( time( NULL ) );
	/* Write random values */
	for ( i = 0; i < w->size; i++ )
		w->data[i] = (rand() % 2) ? MLL_CELL_ALIVE : MLL_CELL_DEAD;
}

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

	w = malloc( sizeof *w );

	w->x = x_size;
	w->y = y_size;
	w->size = w->x * w->y;

	w->data = malloc( x_size * y_size * sizeof *(w->data) );

	world_clear( w );

	return w;
}

void world_resize( world* w, int x_size, int y_size ) {
	w->x = x_size;
	w->y = y_size;
	w->size = w->x * w->y;

	w->data = realloc( w->data, x_size * y_size * sizeof *(w->data) );
}

void world_clear( world* w ) {
	int i;
	for ( i = 0; i < w->size; i++ )
		w->data[i] = 0;
}

void world_free( world* w ) {
	free( w->data );
	free( w );
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
	srand( time( NULL ) );
	for ( i = 0; i < w->size; i++ )
		w->data[i] = (rand() % 2) ? MLL_CELL_ALIVE : MLL_CELL_DEAD;
}

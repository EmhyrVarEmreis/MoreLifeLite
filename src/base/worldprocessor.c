/*
 * worldprocessor.c
 *
 *  Created on: 26 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdio.h>

#include "worldprocessor.h"
#include "world.h"
#include "rules.h"
#include "mll_constants.h"

void worldprocessor_make_cycle_simple( world* w, int torus ) {
	worldprocessor_process_cells( w );
	worldprocessor_post_process_cells( w );
}

void worldprocessor_make_cycle_full( world* w, world* h, int torus ) {
	if ( torus )
		worldprocessor_process_cells_torus( w );
	else
		worldprocessor_process_cells( w );

	if ( h == NULL )
		worldprocessor_post_process_cells( w );
	else
		worldprocessor_post_process_cells_with_heating( w, h );
}

void worldprocessor_process_cells_torus( world* w ) {

	int i, j, x, y;

	/*
	 * TODO Ulepszyæ torus
	 */
	for ( i = 0; i < w->y; i++ )
		for ( j = 0; j < w->x; j++ )
			if ( w->data[j + i * w->x] > MLL_CELL_BORDER )
				for ( y = i - 1; y < i + 2; y++ )
					for ( x = j - 1; x < j + 2; x++ ) {
						/*printf("%d,%d  ->  %d,%d\t\t%d %d\n", x, y, x % w->x, y % w->y, w->x, w->y);*/
						w->data[( x == -1 ? w->x-1 : x % (w->x)) + ( y == -1 ? w->y-1 : y % (w->y)) * w->x]++;
					}
}

void worldprocessor_process_cells( world* w ) {

	int i, j, x, y;

	/* Iterate - cols */
	for ( i = 0; i < w->y; i++ )
		/* Iterate - rows */
		for ( j = 0; j < w->x; j++ )
			/* Take only alive cells */
			if ( w->data[j + i * w->x] > MLL_CELL_BORDER )
				/* Iterate for one backwards and one forwards - cols */
				for ( y = i - 1; y < i + 2 && y < w->y && y >= 0; y++ )
					/* Iterate for one backwards and one forwards - rows */
					for ( x = j - 1; x < j + 2 && x < w->x && x >= 0; x++ )
						/* Incremenation of number of neighbors */
						w->data[x + y * w->x]++;
}

void worldprocessor_post_process_cells( world* w ) {
	int i;

	/* For each cell */
	for ( i = 0; i < w->size; i++ )
		/* Set the proper state of cell */
		w->data[i] = rules_process_cell( w->data[i] );
}

void worldprocessor_post_process_cells_with_heating( world* w, world* h ) {
	int i, j;
	for ( i = 0; i < w->size; i++ ) {
		/*
		 * TODO Mo¿e da siê co jeszcze z tym zrobiæ
		 */
		j = rules_process_cell( w->data[i] );
		if ( !(w->data[i] > MLL_CELL_BORDER) * (j > MLL_CELL_BORDER) ) {
			h->data[i]++;
		}
		w->data[i] = j;
	}
}

int worldprocessor_is_cell_alive( world* w, int x_pos, int y_pos ) {
	return (w->data[x_pos + y_pos * w->x] > MLL_CELL_BORDER) ? 1 : 0;
}

int worldprocessor_alive_cells_count( world* w ) {
	int i, j;
	j = 0;
	for ( i = 0; i < w->size; i++ )
		if ( w->data[i] > MLL_CELL_BORDER )
			j++;
	return j;
}

/*
 * file.c
 *
 *  Created on: 26 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "world.h"
#include "mll_constants.h"
#include "structs.h"

int file_read_world( world* w, char* filename, structs* s ) {

	FILE *f;
	int c;
	int filetype;
	char* tp;
	int x, y;

	f = fopen( filename, "r" );
	if ( f == NULL )
		return 1;

	filetype = 0;

	c = fgetc( f );

	/* Determine filetype */
	if ( c == 'A' )
		filetype = 1;
	else if ( c == 'B' )
		filetype = 2;

	if ( fscanf( f, "%d %d", &(w->x), &(w->y) ) != 2 ) {
		w = NULL;
		return 2;
	}

	/* Set preffered world size */
	world_resize( w, w->x, w->y );
	world_clear( w );

	if ( filetype == 1 ) {
		int x, y;

		x = y = 0;

		/* TODO Optymalizacja - Lepsze czytanie */

		while ((c = fgetc( f )) != '\n')
			;
		if ( c != EOF )
			while ((c = fgetc( f )) != EOF) {
				/* Escape \n */
				if ( c == '\n' ) {
					y++;
					x = 0;
				} else {
					/* Save to grid */
					w->data[x + w->x * y] = (c == 'A' ? MLL_CELL_ALIVE : MLL_CELL_DEAD);
					x++;
				}

				if ( y >= w->y )
					break;

			}

	} else if ( filetype != 2 || s == NULL ) {
		return 3;
	}

	/* Buffer */
	tp = malloc( sizeof *tp * 256 );

	x = y = tp[0] = 0;

	/* Reading structures */
	while (fscanf( f, "%s %d %d", tp, &x, &y ) == 3) {
		/* Inserting to world grid */
		structs_insert_to_world( w, structs_get( s, tp[0] ), x, y );
		/* Escape \n */
		while ((c = fgetc( f )) != '\n')
			if ( c == EOF )
				break;
	}

	fclose( f );

	return 0;

}

int file_save_world( world* w, char* filename, int cycle_number, int alive_cells ) {
	int i;
	FILE* f;

	f = fopen( filename, "wa" );

	if ( f == NULL )
		return 0;

	/* Print filetype and grid size */
	fprintf( f, "A %d %d", w->x, w->y );

	/* Print grid */
	for ( i = 0; i < w->size; i++ ) {
		if ( !(i % w->x) )
			fputc( '\n', f );
		fputc( w->data[i] > MLL_CELL_BORDER ? 'A' : 'D', f );
	}

	fclose( f );

	return 1;
}

FILE* file_stats_gnuplot_init( char* filename ) {
	FILE* f;
	f = fopen( filename, "wa" );
	return f;
}

int file_stats_gnuplot_write( FILE* out, int cycle_number, int alive_cells ) {
	if ( fprintf( out, "%d %d\n", cycle_number, alive_cells ) < 0 )
		return 0;
	return 1;
}

/*
 * structs.c
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "world.h"
#include "mll_constants.h"

structs* structs_init() {
	structs* s;

	s = malloc( sizeof *s );
	s->n = 0;

	return s;
}

int structs_read( char* filename, structs* s ) {
	FILE *f;
	int c, tx, ty;
	char* tc;

	tc = malloc( sizeof *tc * 256 );
	c = 0;
	tc[0] = 0;

	f = fopen( filename, "r" );
	if ( f == NULL )
		return 0;

	while (fscanf( f, "%s %d %d", tc, &tx, &ty ) == 3) {
		if ( struct_add( s, tc[0], world_init( tx, ty ) ) ) {
			tx = 0;
			ty = 0;
			while ((c = fgetc( f )) != '\n')
						;
			while ((c = fgetc( f )) != EOF) {
				if ( c == '\n' ) {
					ty++;
					tx = 0;
				} else {
					s->data[s->n-1]->data[tx + s->data[s->n-1]->x * ty] = (c == 'A' ? MLL_CELL_ALIVE : MLL_CELL_DEAD);
					tx++;
				}

				if ( ty >= s->data[s->n-1]->y )
					break;

			}

		}
	}

	return 1;
}

world* structs_get( structs* s, char id ) {
	int i;
	i = s->n;
	while (i--)
		if ( s->ids[i] == id )
			return s->data[i];
	return NULL;
}

int struct_add( structs* s, char c, world* w ) {
	/*s->data[s->n] = malloc(sizeof *s->data[s->n]);*/
	if ( s->n >= STRUCTS_MAX || structs_get( s, c ) != NULL )
		return 0;
	s->data[s->n] = w;
	s->ids[s->n] = c;
	s->n++;
	return 1;
}

int structs_insert_to_world( world* w, world* s, int x, int y ) {
	int i, j;
	if ( w == NULL || s == NULL )
		return 0;
	if ( s->x + x > w->x || s->y + y > w->y )
		return 0;
	for ( i = 0; i < s->y; i++ ) {
		for ( j = 0; j < s->x; j++ ) {
			w->data[(i + y) * w->x + (j + x)] = s->data[i * s->x + j];
		}
	}
	return 1;
}

void structs_free( structs* s ) {
	while (--s->n)
		world_free( s->data[s->n] );
	free( s );
}

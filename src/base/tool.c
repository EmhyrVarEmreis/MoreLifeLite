/*
 * tool.c
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tool.h"
#include "save.h"
#include "file.h"
#include "options.h"
#include "world.h"
#include "worldprocessor.h"

static int w_alive;
static char buf[256];


/*
 * Replacing strings in paths - works faster than 2x sprintf
 */
void set_path_ext( char* s, char a, char b, char c ) {
	while (*s)
		s++;
	*(--s) = c;
	*(--s) = b;
	*(--s) = a;
	while (*s != '/')
		s--;
	*(--s) = c;
	*(--s) = b;
	*(--s) = a;
}

void tool_make_dump( options* o, world* w, world* h, int n, int* dumps_num ) {
	if ( o->options[3] || o->options[10] )
		w_alive = worldprocessor_alive_cells_count( w );
	else
		w_alive = -2;
	if ( (o->options[0] || o->options[1] || o->options[4] || o->options[7]) && !((n) % o->options[9]) ) {
		(*dumps_num)++;
		sprintf( buf, "%s%.9d.png", o->strings[5], n );
		if ( o->options[0] ) {
			/*sprintf( buf, "%s%d.png", o->strings[5], n );*/
			set_path_ext( buf, 'p', 'n', 'g' );
			save_png( w, buf, n, w_alive );
		}
		if ( o->options[1] ) {
			/*sprintf( buf, "%s%d.svg", o->strings[6], n );*/
			set_path_ext( buf, 's', 'v', 'g' );
			save_svg( w, buf, n, w_alive );
		}
		if ( o->options[7] ) {
			/*sprintf( buf, "%s%d.txt", o->strings[7], n );*/
			set_path_ext( buf, 't', 'x', 't' );
			file_save_world( w, buf, n, w_alive );
		}
		if ( o->options[4] ) {
			world_print( w );
		}
	}

	if ( o->options[10] && !((n) % o->options[10]) )
		file_stats_gnuplot_write( o->gnuplot, n, w_alive );
}

int tool_str_cmp( char* a, char* b, int c ) {
	int i;
	i = 0;
	while (*a == *b && i < c) {
		a++;
		b++;
		i++;
	}
	return i == c ? 1 : 0;
}

int tool_set_world_size( world* w, char* a ) {
	char buf[64];
	int i;

	i = 0;

	while (*a) {
		if ( isdigit( *a ) )
			buf[i++] = *a;
		else
			buf[i++] = ' ';
		a++;
	}
	buf[i] = '\0';

	if ( sscanf( buf, "%d %d", &w->x, &w->y ) == 2 && w->x > 0 && w->y > 0 )
		return 1;
	else
		return 0;

}

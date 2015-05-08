/*
 * options.c
 *
 *  Created on: 28 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>

#include "options.h"
#include "tool.h"

options* options_init() {
	options * o;
	o = malloc( sizeof *o );
	return o;
}

int options_parse( options* o, int argc_a, char** argv_a ) {

	char c;

	while ((c = getopt( argc_a, argv_a, "l:n:r:sgzf:cho:ub:m:tpv" )) != -1)
		switch (c) {
			case 'l':
				if ( optarg != NULL )
					strcpy( o->strings[1], optarg );
				break;
			case 'n':
				if ( atoi( optarg ) > 0 )
					o->options[8] = atoi( optarg );
				break;
			case 'r':
				if ( optarg != NULL )
					strcpy( o->strings[3], optarg );
				break;
			case 's':
				o->options[5] = 1;
				break;
			case 'g':
				o->options[4] = 1;
				break;
			case 'z':
				o->options[6] = 1;
				break;
			case 'f':
				if ( optarg != NULL )
					strcpy( o->strings[0], optarg );
				break;
			case 'c':
				o->options[2] = 1;
				break;
			case 'h':
				o->options[11] = 1;
				break;
			case 'o':
				if ( atoi( optarg ) > 0 )
					o->options[10] = atoi( optarg );
				break;
			case 'u':
				o->options[3] = 0;
				break;
			case 'b':
				if ( optarg != NULL )
					strcpy( o->strings[2], optarg );
				break;
			case 'm':
				if ( atoi( optarg ) > 0 )
					o->options[9] = atoi( optarg );
				break;
			case 't':
				o->options[7] = 1;
				break;
			case 'p':
				o->options[0] = 1;
				break;
			case 'v':
				o->options[1] = 1;
				break;
			case '?':
				if ( optopt == 'c' )
					fprintf( stderr, "Option -%c requires an argument.\n", optopt );
				else if ( isprint( optopt ) )
					fprintf( stderr, "Unknown option `-%c'.\n", optopt );
				else
					fprintf( stderr, "Unknown option character `\\x%x'.\n", optopt );
				return 0;
			default:
				abort();
		}
	return 1;
}

void options_set_defaults( options* o ) {
	int i, n;
	n = sizeof o->options / sizeof o->options[0];
	for ( i = 0; i < n; i++ )
		o->options[i] = 0;
	o->options[3] = 1;
	o->options[9] = 1;
	o->options[8] = 100;
	n = (sizeof o->strings / sizeof o->strings[0]);
	for ( i = 0; i < n; i++ )
		o->strings[i][0] = '\0';
	o->gnuplot = NULL;

}

int options_check_min( int argc, char** argv ) {
	if ( !tool_search_string( argc, argv, "-l" ) && !tool_search_string( argc, argv, "-h" ) ) {
		fprintf( stderr, "Option '-l FILE' is required!\n" );
		return 0;
	} /*else if( !tool_search_string( argc, argv, "-n" ) ) {
	 fprintf( stderr, "Option '-n NUMBER' is required!\n" );
	 return 0;
	 } else if ( !tool_search_string( argc, argv, "-m" ) ) {
	 fprintf( stderr, "Option '-m NUMBER' is required!\n" );
	 return 0;
	 }*/
	return 1;
}

void options_free( options* o ) {
	free( o );
}

/*
 =======================================================================================
 Name        : MoreLifeLite.c
 Author      : Mateusz Stefaniak
 Contact     : mstef94@gmail.com
 Version     : 1.1.8 Beta
 Copyright   : Arrrr! Welcome pirrates!
 Description : Life simulator, Very complex, Really, Ansi(not GANGAM, but similar)-style
 =======================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "base/file.h"
#include "base/help.h"
#include "base/options.h"
#include "base/rules.h"
#include "base/save.h"
#include "base/structs.h"
#include "base/tool.h"
#include "base/world.h"
#include "base/worldprocessor.h"

#ifdef WIN32
int mkdir( char* );
#else
int mkdir (const char *filename, mode_t mode);
#endif

int main( int argc, char** argv ) {

	world* w;
	world* h;
	options* o;
	structs* s;
	clock_t begin, end;
	int n, dumps_num, tmp, step_progress;
	double time_spent;
	char buf[3][256];

	/*
	 * Special definition for ECLIPSE CTD IDE
	 */
#ifdef ECLIPSE
	setvbuf( stdout, NULL, _IONBF, 0 );
	setvbuf( stderr, NULL, _IONBF, 0 );
#endif

	/*
	 * Initializing
	 */
	w = world_init( 0, 0 );
	o = options_init();
	s = structs_init();
	dumps_num = 0;
	step_progress = 0;

	/*
	 * Read options
	 */
	options_set_defaults( o );
	options_parse( o, argc, argv );

	if ( o->options[11] ) {
		help_show();
		options_free( o );
		return EXIT_SUCCESS;
	}

	/*
	 * Rules managing
	 */
	if ( o->strings[3][0] == '\0' )
		rules_set_conway();
	else if ( rules_is_valid( o->strings[3] ) )
		rules_set( o->strings[3] );
	else
		fprintf( stderr, "Unknown rules format.\n" );

	/*
	 * ASCII ART - The most important part of this programm
	 */
	if ( !o->options[5] )
		help_ascii_art();

	/*
	 * Structs read
	 */
	if ( o->strings[2][0] != '\0' ) {
		if ( structs_read( o->strings[2], s ) )
			printf( "Structs loaded: %d\n", s->n );
		else {
			fprintf( stderr, "Structs from file \"%s\" readed incorrectly!\nExiting!\n", o->strings[2] );
			return -3;
		}
	}

	/*
	 * Read file
	 */
	if ( o->strings[1][0] != '\0' ) {
		if ( tool_str_cmp( o->strings[1], "RANDOMIZED", 10 ) ) {
			if ( tool_set_world_size( w, o->strings[1] ) ) {
				world_resize( w, w->x, w->y );
				world_randomize( w );
				if ( !o->options[5] )
					printf( "Grid loaded as RANDOMIZED with size %dx%d\n", w->x, w->y );
			} else {
				if ( !o->options[5] )
					fprintf( stderr, "Grid loading as RANDOMIZED occured a problem!\nExiting!\n" );
				return -2;
			}
		} else {
			tmp = file_read_world( w, o->strings[1], s );
			if ( !o->options[5] ) {
				if ( tmp == 0 )
					printf( "Grid from file \"%s\" readed properly\n", o->strings[1] );
				else if ( tmp == 3 )
					fprintf( stderr, "Grid from file \"%s\" readed incorrectly! No structs to place!\nExiting!\n", o->strings[1] );
				else
					fprintf( stderr, "Grid from file \"%s\" readed incorrectly!\nExiting!\n", o->strings[1] );
			}
			if ( tmp != 0 ) {
				return -1;
			}
		}
	} else {
		fprintf( stderr, "File reading problem!\nExiting!\n" );
		return -1;
	}

	/*
	 * Heat-map initializing
	 */
	if ( o->options[2] )
		h = world_init( w->x, w->y );

	/*
	 * Prepare paths
	 */
	if (o->strings[0][0] != '\0') {
	#ifdef WIN32
		tmp = mkdir( o->strings[0] );
	#else
		tmp = mkdir( o->strings[0], S_IRWXU | S_IRWXG | S_IRWXO );
	#endif
		if ( tmp != -1 ) {
			fprintf( stderr, "Directory '%s' do not exist! Create it first!\nExiting!\n", o->strings[0] );
			return -1;
		}
	}
	sprintf( buf[0], "%s%s%d", (o->strings[0][0] == '\0') ? "" : o->strings[0], (o->strings[0][0] == '\0') ? "" : "/", (int) time( NULL ) );
	strcpy( buf[2], buf[0] );
	sprintf( o->strings[4], "%s/%s", buf[0], "history/" );
	sprintf( o->strings[5], "%s/%s", buf[0], "png/" );
	sprintf( o->strings[6], "%s/%s", buf[0], "svg/" );
	sprintf( o->strings[7], "%s/%s", buf[0], "txt/" );

#ifdef WIN32
	mkdir( buf[0] );
#else
	mkdir( buf[0], S_IRWXU | S_IRWXG | S_IRWXO );
#endif
	sprintf( buf[1], "%s/history", buf[0] );
#ifdef WIN32
	mkdir( buf[1] );
#else
	mkdir( buf[1], S_IRWXU | S_IRWXG | S_IRWXO );
#endif
	sprintf( buf[1], "%s/png", buf[0] );
#ifdef WIN32
	mkdir( buf[1] );
#else
	mkdir( buf[1], S_IRWXU | S_IRWXG | S_IRWXO );
#endif
	sprintf( buf[1], "%s/svg", buf[0] );
#ifdef WIN32
	mkdir( buf[1] );
#else
	mkdir( buf[1], S_IRWXU | S_IRWXG | S_IRWXO );
#endif
	sprintf( buf[1], "%s/txt", buf[0] );
#ifdef WIN32
	mkdir( buf[1] );
#else
	mkdir( buf[1], S_IRWXU | S_IRWXG | S_IRWXO );
#endif

	/*
	 * Open gnuplot file
	 */
	if ( o->options[10] ) {
		sprintf( buf[1], "%sgnuplot.txt", o->strings[4] );
		o->gnuplot = file_stats_gnuplot_init( buf[1] );
		if ( o->gnuplot == NULL ) {
			fprintf( stderr, "Error managing gnuplot file (%s). Program is going to abort generating this file and continue!\n", buf[1] );
			o->options[10] = 0;
		}
	}

	/*
	 * Print info
	 */
	if ( !o->options[5] ) {
		printf( "Generating PNG/SVG/TXT/GNUPLOT_FILE/HEAT_MAP -> %c/%c/%c/%c/%c\n", (o->options[0]) ? '+' : '-', (o->options[1]) ? '+' : '-',
				(o->options[7]) ? '+' : '-', (o->options[10]) ? '+' : '-', (o->options[2]) ? '+' : '-' );
		printf( "Starting...\n" );
	}

	/*
	 * Start measuring time
	 */
	begin = clock();

	/*
	 * Prepare progress
	 */
	step_progress = (o->options[8] / 10 < 1) ? 1 : o->options[8] / 10;

	/*
	 * Start cycling
	 */
	for ( n = 0; n < o->options[8]; n++ ) {
		/*
		 * Make dump
		 */
		dumps_num = tool_make_dump( o, w, h, n, dumps_num, buf[0] );

		/*
		 * Process cells
		 */
		worldprocessor_make_cycle_full( w, h, o->options[6] );

		if ( o->options[4] )
			world_print(w);

		/*
		 * Print progress
		 */
		if ( !o->options[5] && (n % step_progress) == 0 )
			printf( "\t%d%%\n", (int) (100.0 * n / o->options[8]) );
	}

	/*
	 * Ending operations - last dump & save heat map
	 */
	o->options[9] = n;
	dumps_num = tool_make_dump( o, w, h, n, dumps_num, buf[0] );
	if ( o->options[2] ) {
		if ( o->options[0] ) {
			sprintf( buf[0], "%sheating_map_of_changes.png", o->strings[4] );
			save_png_hm( h, buf[0] );
		}
		if ( o->options[1] ) {
			sprintf( buf[0], "%sheating_map_of_changes.svg", o->strings[4] );
			save_svg_hm( h, buf[0] );
		}
	}

	/*
	 * End measuring time
	 */
	end = clock();

	/*
	 * Calculate time
	 */
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

	if ( !o->options[5] ) {
		printf( "Done!\n" );
		printf( "Dumped %d states to '%s%s/'\n", dumps_num, (buf[2][0] == '/') ? "" : "CURRENT_DIRECTORY/", buf[2] );
		printf( "Running time: %gs\n", time_spent );
	}

	/*
	 * Free memory
	 */
	world_free( w );
	if ( h != NULL )
		world_free( h );
	if ( o->gnuplot != NULL )
		fclose( o->gnuplot );
	options_free( o );

	/*
	 * VICTORY!
	 */
	return EXIT_SUCCESS;
}


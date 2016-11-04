/*
 * help.c
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#define HELP_DESCR "It's a simple cellular automaton written in C made for Computer Science\n\
Studies at the Warsaw University of Technology's Faculty of Electrical\n\
Engineering. The program uses the Moore neighborhood, can use custom rules\n\
(defaults the rules of John Conway'a Game of Life) and throws momentary\n\
states in the form of PNG, SVG, TXT and log files for gnuplot."
#define HELP_LONG_1 "Options:\n\
-l FILE\tReads first state from FILE. Type 'RANDOMIZEDXxY to get'\n\
\ta random grid with width X and height Y.\n\
-n NUM\tSet NUM of cycles. Dafaults - 100.\n\
-r RUL\tSet RUL to simulator. Type number of neighbors when alive\n\
\tcell stays alive, then type '/', and type numbers of\n\
\tneighbors when dead cell turns\n"
#define HELP_LONG_2 "\tinto alive one. Defaults - '23/3' (John's Conway's game of life)\n\
-s\tTurn ON silent mode - no unnecessary output to stdout.\n\
-g\tTurn ON writting states to stdout.\n\
-z\tTurn ON torus mode.\n\
-c\tTurn ON generating heat map of changes on grid.\n\
-h\tShows HELP (this) and exits.\n"
#define HELP_LONG_3 "-o NUM\tSet frequency of dumping stats for gnuplot file.\n\
-m NUM\tSet frequency of dumping setted states.\n\
-u\tTurn ON generating statistic to gnuplot readable file.\n\
-b FILE\tRead structures to place on grid from FILE.\n\
-t\tTurn ON dumping states as TXT files.\n\
-p\tTurn ON dumping states as PNG images\n\
-v\tTurn ON dumping states as SVG images.\n"

#include <stdio.h>

#include "options.h"
#include "rules.h"
#include "help.h"

#define TOOL_OPT(O)  ( O ? '+' : '-' )

void help_ascii_art() {
	printf(
			"    __  ___                __    _ ____     __    _ __     \n   /  |/  ____  ________  / /   (_/ _____  / /   (_/ /____ \n  / /|_/ / __ \\/ ___/ _ \\/ /   / / /_/ _ \\/ /   / / __/ _ \\\n / /  / / /_/ / /  /  __/ /___/ / __/  __/ /___/ / /_/  __/\n/_/  /_/\\____/_/   \\___/_____/_/_/  \\___/_____/_/\\__/\\___/ \n\n" );
	printf( "\n\t\t   Version 1.2.3 Beta\n\n" );
}

void help_print_line() {
	printf( "------------------------------------------------------------\n" );
}

void help_show() {
	help_ascii_art();
	help_print_line();
	printf( "\n%s\n\n", HELP_DESCR );
	help_print_line();
	printf( "\n%s%s%s", HELP_LONG_1, HELP_LONG_2, HELP_LONG_3 );
}

void help_print_options( options* o ) {
	printf( "\tCYCLES\t\t%-14d  STEP\t\t%d\n\tPNG\t\t%c\t\tSVG\t\t%c\n\tTXT\t\t%c\t\tGNUPLOT_FILE\t%c\n\tHEAT_MAP\t%c\t\tRULES\t\t%s\n", o->options[8],
			o->options[9], TOOL_OPT( o->options[0] ), TOOL_OPT( o->options[1] ), TOOL_OPT( o->options[7] ), TOOL_OPT( o->options[10] ),
			TOOL_OPT( o->options[2] ), (o->strings[3][0] == '\0') ? "23/3" : (rules_is_valid( o->strings[3] )) ? o->strings[3] : "?/?" );
}

/*
 * help.c
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdio.h>

#include "options.h"
#include "rules.h"

#define TOOL_OPT(O)  ( O ? '+' : '-' )

void help_ascii_art() {
	printf(
			"    __  ___                __    _ ____     __    _ __     \n   /  |/  ____  ________  / /   (_/ _____  / /   (_/ /____ \n  / /|_/ / __ \\/ ___/ _ \\/ /   / / /_/ _ \\/ /   / / __/ _ \\\n / /  / / /_/ / /  /  __/ /___/ / __/  __/ /___/ / /_/  __/\n/_/  /_/\\____/_/   \\___/_____/_/_/  \\___/_____/_/\\__/\\___/ \n\n" );
	printf( "\n\t\t   Version 1.2.1 Beta\n\n" );
}

void help_show() {
	printf( "Ask MS Clippy\n __\n\
/  \\\n\
|  |\n\
@  @\n\
|| ||\n\
|| ||\n\
|\\_/|\n\
\\___/ \n" );

}

void help_print_line() {
	printf( "------------------------------------------------------------\n" );
}

void help_print_options( options* o ) {
	printf( "\tCYCLES\t\t%-14d  STEP\t\t%d\n\tPNG\t\t%c\t\tSVG\t\t%c\n\tTXT\t\t%c\t\tGNUPLOT_FILE\t%c\n\tHEAT_MAP\t%c\t\tRULES\t\t%s\n", o->options[8],
			o->options[9], TOOL_OPT( o->options[0] ), TOOL_OPT( o->options[1] ), TOOL_OPT( o->options[7] ), TOOL_OPT( o->options[10] ),
			TOOL_OPT( o->options[2] ), (o->strings[3][0] == '\0') ? "23/3" : (rules_is_valid( o->strings[3] )) ? o->strings[3] : "?/?" );
}

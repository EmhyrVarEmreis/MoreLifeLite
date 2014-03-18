/*
 * save.c
 *
 *  Created on: 28 lut 2014
 *      Author: Mateusz Stefaniak
 */

#include <stdio.h>
#include <stdlib.h>

#include "save.h"
#include "world.h"
#include "mll_constants.h"
#include "worldprocessor.h"
#include "lodepng.h"

int save_svg( world* w, char* filename, int cycle, int alive ) {
	FILE *out;
	int i, j;

	/*
	 * TODO Optymalizacja zapisu SVG
	 */

	out = fopen( filename, "wa" );
	if ( out == NULL )
		return 1;

	fprintf( out,
			"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.0\" width=\"%d\" height=\"%d\"><g id=\"sharp\" transform=\"translate(0.5,0.5)\">\n",
			(w->x * 8 + 1 > 230) ? w->x * 8 + 1 : 230, w->y * 8 + 30 );

	for ( i = 0; i < w->y; i++ ) {
		for ( j = 0; j < w->x; j++ ) {
			if ( w->data[i * w->x + j] > MLL_CELL_BORDER )
				fprintf( out, "<circle cx=\"%d\" cy=\"%d\" r=\"3\" fill=\"black\" />\n", 4 + j * 8, 4 + i * 8 );
			if ( i == 0 )
				fprintf( out, "<line x1=\"%d\" y1=\"0\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", j * 8, j * 8, w->y * 8 );
		}
		fprintf( out, "<line x1=\"%d\" y1=\"0\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", j * 8, j * 8, w->y * 8 );
		fprintf( out, "<line x1=\"0\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", i * 8, w->x * 8, i * 8 );
	}
	fprintf( out, "<line x1=\"0\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", i * 8, w->x * 8, i * 8 );

	/* Informacje statystyczne */
	if ( cycle >= 0 && alive != -2 ) {
		int t;
		t = (alive >= 0) ? alive : worldprocessor_alive_cells_count( w );
		fprintf( out, "<text x=\"0\" y=\"%d\" fill=\"black\" style=\"font-family: Consolas, Tahoma, 'Arial Narrow', Arial;\">Cycle: %d</text>\n",
				(i + 1) * 8 + 4, cycle );
		fprintf( out, "<text x=\"0\" y=\"%d\" fill=\"black\" style=\"font-family: Consolas, Tahoma, 'Arial Narrow', Arial;\">Alive: %d (%.2g%%) of %d</text>\n",
				(i + 1) * 8 + 4 + 15, t, t * 100.0 / w->size, w->size );
	}

	fprintf( out, "</g></svg>\n" );

	fclose( out );

	return 0;
}

int save_png( world* w, char* filename, int cycle, int alive ) {
	int i, error;
	unsigned char* image = malloc( w->size * 4 );

	i = 0;

	for ( i = 0; i < w->size; i++ )
		if ( w->data[i] > MLL_CELL_BORDER ) {
			image[4 * i + 0] = 0;
			image[4 * i + 1] = 0;
			image[4 * i + 2] = 0;
			image[4 * i + 3] = 255;
		} else {
			image[4 * i + 0] = 255;
			image[4 * i + 1] = 255;
			image[4 * i + 2] = 255;
			image[4 * i + 3] = 255;
		}

	error = lodepng_encode32_file( filename, image, w->x, w->y );

	free( image );

	if ( error ) {
		fprintf( stderr, "Error png (%s) - %u: %s\n", filename, error, lodepng_error_text( error ) );
		return 1;
	}

	return 0;
}

int save_svg_hm( world* w, char* filename ) {
	FILE *out;
	int i, j, max;
	double skok;

	/*
	 * TODO Optymalizacja zapisu SVG
	 */

	out = fopen( filename, "wa" );
	if ( out == NULL )
		return 1;

	max = 0;

	for ( i = 0; i < w->size; i++ )
		if (w->data[i] > max)
			max  = w->data[i];

	skok = 255.0 / max;

	fprintf( out,
			"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.0\" width=\"%d\" height=\"%d\"><g id=\"sharp\" transform=\"translate(0.5,0.5)\">\n",
			w->x * 8 + 1, w->y * 8 + 1 );

	for ( i = 0; i < w->y; i++ ) {
		for ( j = 0; j < w->x; j++ ) {
			fprintf( out, "<circle cx=\"%d\" cy=\"%d\" r=\"3\" fill=\"rgb(%d,%d,%d)\" />\n", 4 + j * 8, 4 + i * 8, 255, 255-(int)(skok*w->data[i * w->x + j]), 255-(int)(skok*w->data[i * w->x + j]) );
			if ( i == 0 )
				fprintf( out, "<line x1=\"%d\" y1=\"0\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", j * 8, j * 8, w->y * 8  );
		}
		fprintf( out, "<line x1=\"%d\" y1=\"0\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", j * 8, j * 8, w->y * 8 );
		fprintf( out, "<line x1=\"0\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", i * 8, w->x * 8, i * 8 );
	}
	fprintf( out, "<line x1=\"0\" y1=\"%d\" x2=\"%d\" y2=\"%d\" style=\"stroke:rgb(166,166,166);stroke-width:1\" />\n", i * 8, w->x * 8, i * 8 );

	fprintf( out, "</g></svg>\n" );

	fclose( out );
	return 0;
}

int save_png_hm( world* w, char* filename ) {
	int i, error, max;
	double skok;
	unsigned char* image = malloc( w->size * 4 );

	i = max = 0;

	for ( i = 0; i < w->size; i++ )
		if (w->data[i] > max)
			max = w->data[i];

	skok = 255.0 / max;

	for ( i = 0; i < w->size; i++ ) {
		image[4 * i + 0] = 255;
		image[4 * i + 1] = 255-(int)(skok*w->data[i]);
		image[4 * i + 2] = 255-(int)(skok*w->data[i]);
		image[4 * i + 3] = 255;
	}

	error = lodepng_encode32_file( filename, image, w->x, w->y );

	free( image );

	if ( error ) {
		fprintf( stderr, "Error png (%s) - %u: %s\n", filename, error, lodepng_error_text( error ) );
		return 1;
	}

	return 0;
}

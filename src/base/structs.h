/*
 * structs.h
 *
 *  Created on: 25 lut 2014
 *      Author: Mateusz Stefaniak
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_
#define STRUCTS_MAX 52

#include "world.h"

typedef struct {
		world*	data[STRUCTS_MAX];
		char	ids[STRUCTS_MAX];
		int		n;
} structs;

/**
 * Makes initialization of structure with world structures.
 * @return				POINTER TO STRUCTURES
 */
structs*	structs_init			( );

/**
 * Reads world structures from file and saves it in structs (s).
 * @param filename		NAME OF FILE TO OPEN AND READ
 * @param s				POINTER TO STRUCTURES
 * @return				RESULT - 0/1 INCORRECTLY/PROPERLY
 */
int			structs_read			( char* filename, structs* s );

/**
 * Returns structure by ID (char) from structs.
 * @param s				POINTER TO STRUCTURES
 * @param id			ID OF WORLD STRUCTURE
 * @return				NULL IF DO NOT EXISTS OR POINTER
 */
world*		structs_get				( structs* s, char id );

/**
 * Adds world structure to structs.
 * @param s				POINTER TO STRUCTURES
 * @param c				ID OF WORLD STRUCTURE
 * @param w				POINTER TO WORLD WITH STRUCTURE TO ADD
 * @return				RESULT - 0/1 INCORRECTLY/PROPERLY
 */
int			struct_add				( structs* s, char c, world* w );

/**
 * Inserts structure to existing world.
 * @param w				POINTER TO WORLD
 * @param s				POINTER TO STRUCTURE
 * @param x				POSITION X
 * @param y				POSITION Y
 * @return				RESULT - 0/1 INCORRECTLY/PROPERLY
 */
int			structs_insert_to_world	( world* w, world* s , int x, int y );

/**
 * Frees memory of structs.
 * @param s				POINTER TO STRUCTS
 */
void		structs_free			( structs* s );



#endif /* STRUCTS_H_ */

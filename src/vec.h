#pragma once

#include <stdlib.h>

#define vec_struc( t, a )                                                      \
	{                                                                          \
		t* data;                                                               \
		a size;                                                                \
		a cap;                                                                 \
	}

#define vec_type( t, a )                                                       \
	typedef struct vec_##t##_##a vec_struc( t, a ) vec_##t##_##a

#define vec_push( v )                                                          \
	if ( ++( v ).size >= ( v ).cap ) {                                         \
		( v ).cap *= 2;                                                        \
		( v ).data = realloc( ( v ).data, sizeof( *( v ).data ) * ( v ).cap ); \
	}                                                                          \
	( v ).data[ ( v ).size - 1 ] =

#define vec_pop( v )                                                           \
	if ( --( v ).size >= v.cap / 2 ) {                                         \
		( v ).cap /= 2;                                                        \
		( v ).data = realloc( ( v ).data, sizeof( *( v ).data ) * ( v ).cap ); \
	}

#define vec_init( t, a )                                                       \
	( vec_##t##_##a ){ .data = malloc( sizeof( t ) ), .size = 0, .cap = 1 }

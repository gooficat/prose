#pragma once

#include <stdlib.h>

#define vec_type( t, a )                                                       \
	struct {                                                                   \
		t* data;                                                               \
		a size;                                                                \
		a cap;                                                                 \
	}

#define push( v )                                                              \
	if ( ++( v ).size >= ( v ).cap ) {                                         \
		( v ).cap *= 2;                                                        \
		( v ).data = realloc( ( v ).data, sizeof( *( v ).data ) * ( v ).cap ); \
	}                                                                          \
	( v ).data[ ( v ).size - 1 ] =

#define pop( v )                                                               \
	if ( --( v ).size >= v.cap / 2 ) {                                         \
		( v ).cap /= 2;                                                        \
		( v ).data = realloc( ( v ).data, sizeof( *( v ).data ) * ( v ).cap ); \
	}

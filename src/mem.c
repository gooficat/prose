#include "mem.h"
#include <stdlib.h>
#include <string.h>
#include "vec.h"

mem_tracker_t create_mem_tracker()
{
	return (mem_tracker_t){
		.data = malloc( sizeof( pvoid ) ),
		.size = 0,
		.cap = 1,
	};
}

void clear_mem_tracker( mem_tracker_t* mt )
{
	for ( size_t i = 0; i < mt->size; ++i )
	{
		free( mt->data[ i ] );
	}
	free( mt->data );
}

void* tracked_malloc( mem_tracker_t* mt, size_t size )
{
	void* mem = malloc( size );
	vec_push( *mt ) mem;
	return mem;
}

void* tracked_memdup( mem_tracker_t* mt, void* data, size_t len )
{
	void* mem = tracked_malloc( mt, len );
	memcpy_s( mem, len, data, len );
	return mem;
}

char* tracked_strdup( mem_tracker_t* mt, const char* s1 )
{
	size_t len = strlen( s1 );
	void* mem = tracked_malloc( mt, len + 1 );
	strcpy_s( mem, len, s1 );
	return mem;
}

#include "mem.h"
#include <stdlib.h>
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

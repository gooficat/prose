#pragma once

#include <stdint.h>
#include "vec.h"

typedef void* pvoid;

typedef struct vec_struc( pvoid, uint16_t ) mem_tracker_t;

mem_tracker_t create_mem_tracker();

void clear_mem_tracker( mem_tracker_t* mt );

void* tracked_malloc( mem_tracker_t* mt, size_t size );

void* tracked_memdup( mem_tracker_t* mt, void* data, size_t len );

char* tracked_strdup( mem_tracker_t* mt, const char* s1 );

#define tracked_vec_init( mt, t, a )                                           \
	( vec_##t##_##a ){ .data = tracked_malloc( &( mt ), sizeof( t ) ),         \
					   .size = 0,                                              \
					   .cap = 1 }

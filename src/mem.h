#pragma once

#include <stdint.h>
#include "vec.h"

typedef void* pvoid;

typedef struct vec_struc( pvoid, uint16_t ) mem_tracker_t;

mem_tracker_t create_mem_tracker();

void clear_mem_tracker( mem_tracker_t* mt );

void* tracked_malloc( mem_tracker_t* mt, size_t size );

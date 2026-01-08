#pragma once
#include "class.h"
#include "types.h"
#include "vector.h"

typedef void *PVoid;

vec_type(PVoid, u32);

class(HallocTracker)
{
	vector_PVoid_u32 elements;
};

HallocTracker CreateHallocTracker();

void *Halloc(HallocTracker *tracker, size_t size);
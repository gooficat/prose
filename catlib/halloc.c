#include "halloc.h"
#include "vector.h"

#include <stddef.h>
#include <stdlib.h>

HallocTracker CreateHallocTracker()
{
	HallocTracker tracker;
	tracker.elements = create_vector(PVoid, u32);
	return tracker;
}

void HallocTrackBlock(HallocTracker *tracker, PVoid element)
{
	push(tracker->elements, element);
}

PVoid Halloc(HallocTracker *tracker, size_t size)
{
	void *data = malloc(size);
	push(tracker->elements, data);
	return data;
}

void EmptyHallocTracker(HallocTracker *tracker)
{
	for (u32 i = tracker->elements.size; i != 0; --i)
	{
		if (tracker->elements.data[i])
		{
			free(tracker->elements.data[i]);
			pop(tracker->elements);
		}
	}
}
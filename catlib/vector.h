#pragma once

#include <stdlib.h>

#define vec_type(t, i)                                                                                                 \
	typedef struct vector_##t##_##i                                                                                    \
	{                                                                                                                  \
		t *data;                                                                                                       \
		i size;                                                                                                        \
		i capacity;                                                                                                    \
	} vector_##t##_##i;

#define vector(t, i) vector_##t##_##i

#define create_vector(t, i)                                                                                            \
	(vector_##t##_##i){                                                                                                \
		.data = malloc(sizeof(t)),                                                                                     \
		.size = 0,                                                                                                     \
		.capacity = 1,                                                                                                 \
	};

#define push(v, ...)                                                                                                   \
	++(v).size;                                                                                                        \
	if ((v).capacity <= (v).size)                                                                                      \
	{                                                                                                                  \
		(v).capacity *= 2;                                                                                             \
		(v).data = realloc((v).data, sizeof((v).data[0]) * (v).capacity);                                              \
	}                                                                                                                  \
	(v).data[(v).size - 1] = __VA_ARGS__;

#define pop(v)                                                                                                         \
	--(v).size;                                                                                                        \
	if ((v).capacity / 2 > (v).size)                                                                                   \
	{                                                                                                                  \
		(v).capacity /= 2;                                                                                             \
		(v).data = realloc((v).data, sizeof((v).data[0]) * (v).capacity);                                              \
	}

#define at(i) data[i]
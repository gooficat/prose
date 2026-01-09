#pragma once

#include <stdint.h>

typedef struct
{
	void *data;
	size_t size;
	size_t cap;
} vec_t;

#define vec_type(t)                                                                                                    \
	struct                                                                                                             \
	{                                                                                                                  \
		t *data;                                                                                                       \
		size_t size;                                                                                                   \
		size_t cap;                                                                                                    \
	}

void init_vec_f(vec_t *v, uint8_t el_size);
#define init_vec(v) init_vec_f((vec_t *)&(v), sizeof((v).data[0]))

void pop_vec_f(vec_t *vec, uint8_t el_size);
#define pop_vec(v) pop_vec_f(&(v), sizeof((v).data[0]))

void push_vec_f(vec_t *vec, const void *data, uint8_t el_size);
#define push_vec(v, d) push_vec_f(&(v), d, sizeof((v).data[0]))

char *copy_str(const char *str);

void *copy_any(const void *data, size_t size);
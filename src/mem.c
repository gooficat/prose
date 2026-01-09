#include "mem.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

char *copy_str(const char *str)
{
	size_t s = strlen(str) + 1;
	char *n = malloc(s);
	strcpy_s(n, s, str);
	return n;
}

void *copy_any(const void *data, size_t size)
{
	void *n = malloc(size);
	memcpy_s(n, size, data, size);
	return n;
}

void init_vec_f(vec_t *v, uint8_t el_size)
{
	v->size = 0;
	v->cap = 0;
	v->data = malloc(el_size);
}

void push_vec_f(vec_t *vec, const void *data, uint8_t el_size)
{
	if (++vec->size > vec->cap)
	{
		vec->cap *= 2;
		vec->data = realloc(vec->data, vec->cap * el_size);
	}
	memcpy_s(vec->data + el_size * (vec->size - 1), el_size, data, el_size);
}

void pop_vec_f(vec_t *vec, uint8_t el_size)
{
	if (--vec->size < vec->cap / 2)
	{
		vec->cap /= 2;
		vec->data = realloc(vec->data, vec->cap * el_size);
	}
}

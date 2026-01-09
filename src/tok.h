#pragma once

#include "mem.h"
#include <stdbool.h>
#include <stdio.h>

typedef vec_type(char *) str_vec;

typedef struct
{
	char *name;
	str_vec args;
	str_vec contents;
} macro_t;

#define TOKEN_MAX_SIZE 32
typedef struct
{
	FILE *file;
	char token[TOKEN_MAX_SIZE];
	int c;
	bool macro_mode;
	macro_t *current_macro;
	size_t macro_seeker;
	vec_type(macro_t) macros;
} tok_stream_t;

tok_stream_t create_tok_stream(const char *path);
void fetch_token(tok_stream_t *ts);
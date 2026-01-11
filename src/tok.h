#pragma once

#include <stdio.h>

#define TOK_MAX 64

typedef struct {
	char tok[ TOK_MAX ];
	FILE* f;
	int c;
} tok_stream_t;

tok_stream_t create_tok_stream( const char* path );

void get_tok( tok_stream_t* ts );

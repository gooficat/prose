#pragma once

#include <stdint.h>
#include "tok.h"
#include "vec.h"

typedef enum {
	PASS_LABEL,
	PASS_ALIGN,
	PASS_WRITE,
	PASS_DONE,
} asm_pass_t;

typedef struct {
	char* name;
	uint64_t offs;
} lab_t;

vec_type( lab_t, uint16_t );

typedef struct {
	tok_stream_t ts;
	size_t offs;
	vec_lab_t_uint16_t labels;
	FILE* out;
	asm_pass_t pass;
} asm_block_t;

lab_t* find_label( asm_block_t* bk, const char* name );

void assemble( const char* in_path, const char* out_path );

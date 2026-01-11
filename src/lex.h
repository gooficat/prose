#pragma once

#include "tok.h"
typedef enum {
	TOK_EOF,
	TOK_LIT,
	TOK_IDT,
	TOK_BRL = '(',
	TOK_BRR = ')',
	TOK_CRL = '{',
	TOK_CRR = '}',
	TOK_SEM = ';',
	TOK_COM = ',',
} tok_type_t;

typedef struct {
	tok_type_t type;
	union
	{
		unsigned long long uval;
		long long ival;
		char* sval;
	};
} token_t;

token_t* read_tokens( tok_stream_t* ts );

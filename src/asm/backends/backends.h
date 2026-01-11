#pragma once
#include "asm/asm.h"

typedef void ( *handle_ins_func )( asm_block_t* bk );

typedef struct {
	const char* name;
	void ( *handle_ins )( asm_block_t* bk );
} backend_t;

extern const backend_t backends[];

void backend_handle_ins( asm_block_t* bk );

void set_backend( const char* name );

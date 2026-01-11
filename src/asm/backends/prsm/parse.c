#include "parse.h"
#include <stdint.h>
#include <string.h>

#define PRSM_MNEM_MAX 8

typedef enum {
	PRSM_ARG_NON,
	PRSM_ARG_IMM,
	PRSM_ARG_MEM,
} prsm_arg_type_t;

typedef struct {
	prsm_arg_type_t type;
	union
	{
		uint64_t uval;
		int64_t ival;
	};
} prsm_arg_t;

typedef struct {
	char mnem[ PRSM_MNEM_MAX ];
	prsm_arg_t arg;
} prsm_ins_t;

typedef enum {
	PRSM_PROF_IMPL,
	PRSM_PROF_SOFF,
	PRSM_PROF_IMMQ,
	PRSM_PROF_RELB,
} prsm_prof_t;

typedef struct {
	const char* mnem;
	prsm_prof_t prof;
} prsm_opc_t;

static const prsm_opc_t prsm_ops[] = {
	{ "halt", PRSM_PROF_IMPL },
	{ "jmp", PRSM_PROF_RELB },
	{ "push", PRSM_PROF_IMMQ },
	{ "pop", PRSM_PROF_IMPL },

};

bool prsm_prof_match( asm_block_t* bk, const prsm_ins_t* ins,
					  const prsm_opc_t* opc )
{
	switch ( ins->arg.type ) {
	case PRSM_ARG_NON:
		return ( opc->prof == PRSM_PROF_IMPL );
	case PRSM_ARG_IMM:
		return opc->prof == PRSM_PROF_IMMQ;
	case PRSM_ARG_MEM:
		if ( opc->prof == PRSM_PROF_RELB ) {
			int64_t rel = bk->offs + 2 + ins->arg.ival;
			return ( rel <= INT8_MAX || rel >= INT8_MIN );
		} else
			return false;
	}
}

uint8_t prsm_find_opc( asm_block_t* bk, const prsm_ins_t* ins )
{
	for ( uint8_t i = 0; i != sizeof( prsm_ops ) / sizeof( prsm_ops[ 0 ] );
		  ++i ) {
		if ( !strcmp( ins->mnem, prsm_ops[ i ].mnem ) &&
			 prsm_prof_match( bk, ins, &prsm_ops[ i ] ) ) {
			return i;
		}
	}
	fprintf( stderr, "No matching instruction profile for mnemonic %s\n",
			 ins->mnem );
}

void prsm_handle_ins( asm_block_t* bk ) {}

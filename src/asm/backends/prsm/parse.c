#include "parse.h"
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
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
	uint8_t code;
	prsm_prof_t prof;
} prsm_opc_t;

static const prsm_opc_t prsm_ops[] = {
	{ "halt", 0, PRSM_PROF_IMPL },
	{ "jmp", 0, PRSM_PROF_RELB },
	{ "push", 0, PRSM_PROF_IMMQ },
	{ "pop", 0, PRSM_PROF_IMPL },

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
			return ( bk->pass == PASS_LABEL || rel <= INT8_MAX ||
					 rel >= INT8_MIN );
		} else
			return opc->prof == PRSM_PROF_SOFF;
	}
}

const prsm_opc_t* prsm_find_opc( asm_block_t* bk, const prsm_ins_t* ins )
{
	for ( uint8_t i = 0; i != sizeof( prsm_ops ) / sizeof( prsm_ops[ 0 ] );
		  ++i ) {
		if ( !strcmp( ins->mnem, prsm_ops[ i ].mnem ) &&
			 prsm_prof_match( bk, ins, &prsm_ops[ i ] ) ) {
			return &prsm_ops[ i ];
		}
	}
	fprintf( stderr, "No matching instruction profile for mnemonic %s\n",
			 ins->mnem );
	exit( EXIT_FAILURE );
}

void prsm_encode( asm_block_t* bk, prsm_ins_t* ins )
{
	const prsm_opc_t* opc = prsm_find_opc( bk, ins );

	puts( "Encoding\n" );
	if ( bk->pass == PASS_WRITE ) {
		fputc( opc->code, bk->out );
		bk->offs = 8;
	}

	switch ( opc->prof ) {
	case PRSM_PROF_IMPL:
		if ( bk->pass == PASS_WRITE ) {
			++bk->offs;
		}
		break;
	case PRSM_PROF_RELB:
		if ( bk->pass == PASS_WRITE ) {
			fputc( ins->arg.ival & 0xFF, bk->out );
		}
		bk->offs += 2;
		break;
	case PRSM_PROF_IMMQ:
	case PRSM_PROF_SOFF:
		if ( bk->pass == PASS_WRITE ) {
			printf( "writing\n" );
			for ( uint8_t i = 0; i != sizeof( uint64_t ); ++i ) {
				fputc( ( ins->arg.ival >> ( 8 * i ) ) & 0xFF, bk->out );
			}
		}
		bk->offs += 9;
		break;
	}
	printf( "Encoding finished, offset %llu\n", bk->offs );
}

void prsm_handle_ins( asm_block_t* bk )
{
	prsm_ins_t ins;
	strcpy_s( ins.mnem, PRSM_MNEM_MAX, bk->ts.tok );
	printf( "Instruction %s\n", ins.mnem );
	skip_wsp( &bk->ts );
	if ( bk->ts.c == '$' ) {
		ins.arg.type = PRSM_ARG_MEM;
		skip_c( &bk->ts );
		get_tok( &bk->ts );
		ins.arg.ival = num_or_label( bk );
	} else if ( isdigit( bk->ts.c ) ) {
		ins.arg.type = PRSM_ARG_IMM;
		get_tok( &bk->ts );
		ins.arg.ival = num_or_label( bk );
	} else {
		ins.arg.type = PRSM_ARG_NON;
	}
	get_tok( &bk->ts );
	prsm_encode( bk, &ins );
}

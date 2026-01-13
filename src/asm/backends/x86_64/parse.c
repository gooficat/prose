#include "parse.h"

#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include "asm/asm.h"
#include "opcodes.h"
#include "tok.h"

typedef struct
{
	x64_reg_t* base;
	x64_reg_t* index;
	uint8_t scale;
	int64_t disp;
} x64_mem_arg_t;

typedef enum
{
	X64_ARG_REG,
	X64_ARG_MEM,
	X64_ARG_IMM,
} x64_arg_type_t;

typedef struct
{
	x64_arg_type_t type;
	union
	{
		x64_reg_t* reg;
		x64_mem_arg_t mem;
		uint64_t imm;
	};
} x64_arg_t;

typedef struct
{
	char name[ X64_MNEM_MAX ];
	x64_arg_t args[ X64_ARG_MAX ];
	uint8_t num_args;
} x64_ins_t;

x64_mnem_t* find_mnem( asm_block_t* bk )
{
	for ( uint16_t i = 0; i != num_mnems; ++i )
	{
		if ( !strcmp( bk->ts.tok, mnems[ i ].name ) )
		{
			return &mnems[ i ];
		}
	}
	return NULL;
}

x64_reg_t* find_reg( asm_block_t* bk )
{
	get_tok( &bk->ts );
	for ( uint8_t i = 0; i != num_regs; ++i )
	{
		if ( !strcmp( bk->ts.tok, regs[ i ].name ) )
		{
			return &regs[ i ];
		}
	}
	return NULL;
}

x64_mem_arg_t parse_mem_arg( asm_block_t* bk )
{
	x64_mem_arg_t arg;

	if ( bk->ts.tok[ 0 ] != '(' )
	{
		arg.disp = num_or_label( bk );
		get_tok( &bk->ts );
		printf( "Displacement %lli\n", arg.disp );
	}
	else
	{
		arg.disp = 0;
	}

	if ( bk->ts.tok[ 0 ] == '(' )
	{
		get_tok( &bk->ts );
		if ( bk->ts.tok[ 0 ] == '%' )
		{
			arg.base = find_reg( bk );
			get_tok( &bk->ts );
			printf( "Base %hhu\n", arg.base->code );
		}
		else
		{
			arg.base = NULL;
		}
		if ( bk->ts.tok[ 0 ] == ',' )
		{
			get_tok( &bk->ts );
		}
		else
		{
			goto end;
		}

		if ( bk->ts.tok[ 0 ] == '%' )
		{
			arg.index = find_reg( bk );
			get_tok( &bk->ts );
			printf( "Index %hhu\n", arg.index->code );
		}
		else
		{
			arg.base = NULL;
		}
		if ( bk->ts.tok[ 0 ] == ',' )
		{
			get_tok( &bk->ts );
		}
		else
		{
			goto end;
		}

		if ( isdigit( bk->ts.tok[ 0 ] ) )
		{
			arg.scale = num_or_label( bk );
			get_tok( &bk->ts );
			printf( "Scale %hhu\n", arg.scale );
		}
	}
	// get_tok( &bk->ts );
end:;
	printf( "Memory arg ends at '%s', has disp %lld, scale %hhu, base %llu, "
			"index %llu\n",
			bk->ts.tok, arg.disp, arg.scale, arg.base, arg.index );

	return arg;
}

void x64_asm_handle_ins( asm_block_t* bk )
{
	x64_ins_t ins;
	ins.num_args = 0;
	strcpy_s( ins.name, X64_MNEM_MAX, bk->ts.tok );

	get_tok( &bk->ts );
	if ( bk->ts.tok[ 0 ] &&
		 ( !isalpha( bk->ts.tok[ 0 ] ) || !find_mnem( bk ) ) )
	// alternatively we could use newline as the end
	{
	parse_arg:;
		printf( "Arg starting with '%s'\n", bk->ts.tok );
		switch ( bk->ts.tok[ 0 ] )
		{
		case '$':
			get_tok( &bk->ts );
			ins.args[ ins.num_args ].type = X64_ARG_IMM;
			ins.args[ ins.num_args ].imm = num_or_label( bk );
			break;
		case '%':
			ins.args[ ins.num_args ].type = X64_ARG_REG;
			ins.args[ ins.num_args ].reg = find_reg( bk );
			break;
		default:
			ins.args[ ins.num_args ].type = X64_ARG_MEM;
			ins.args[ ins.num_args ].mem = parse_mem_arg( bk );
			break;
		}
		++ins.num_args;
		get_tok( &bk->ts );
		if ( bk->ts.tok[ 0 ] == ',' )
		{
			get_tok( &bk->ts );
			printf( "Comma\n" );
			goto parse_arg;	 // i am NOT using a loop. cry harder
		}
		else
		{
			printf( "Not a comma %s\n", bk->ts.tok );
		}
	}

	printf( "Instruction %s with %hhu args\n", ins.name, ins.num_args );
}

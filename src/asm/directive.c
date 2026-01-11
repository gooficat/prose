#include "directive.h"
#include <string.h>
#include "asm.h"

void direc_byte( asm_block_t* bk, uint8_t n )
{
	get_tok( &bk->ts );
	uint64_t v = num_or_label( bk );
	put_bytes( bk, &v, n );
	get_tok( &bk->ts );
}

void direc_align( asm_block_t* bk )
{
	get_tok( &bk->ts );
	uint64_t v = num_or_label( bk );
	skip_wsp( &bk->ts );
	if ( bk->ts.c != ',' )
	{
		while ( bk->offs % v != 0 )
		{
			put_byte( bk, 0 );
		}
	}
	else
	{
		skip_c( &bk->ts );
		get_tok( &bk->ts );
		uint64_t v2 = num_or_label( bk );
		v = v & 0xFF;
		while ( bk->offs % v2 != 0 )
		{
			put_byte( bk, v );
		}
	}
	get_tok( &bk->ts );
}

void handle_directive( asm_block_t* bk )
{
	if ( !strcmp( bk->ts.tok, "byte" ) )
	{
		direc_byte( bk, 1 );
	}
	else if ( !strcmp( bk->ts.tok, "word" ) )
	{
		direc_byte( bk, 2 );
	}
	else if ( !strcmp( bk->ts.tok, "dword" ) )
	{
		direc_byte( bk, 4 );
	}
	else if ( !strcmp( bk->ts.tok, "qword" ) )
	{
		direc_byte( bk, 8 );
	}
	else if ( !strcmp( bk->ts.tok, "align" ) )
	{
		direc_align( bk );
	}
	else if ( !strcmp( bk->ts.tok, "org" ) )
	{
		get_tok( &bk->ts );
		uint64_t v = num_or_label( bk );
		bk->offs = v;
		get_tok( &bk->ts );
	}
	else
	{
		fprintf( stderr, "Unknown directive '%s'\n", bk->ts.tok );
		exit( EXIT_FAILURE );
	}
}

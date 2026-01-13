#include "asm.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "backends/backends.h"
#include "directive.h"
#include "tok.h"
#include "vec.h"

lab_t* find_label( asm_block_t* bk, const char* name )
{
	for ( size_t i = 0; i < bk->labels.size; ++i )
	{
		if ( !strcmp( bk->labels.data[ i ].name, name ) )
		{
			return &bk->labels.data[ i ];
		}
	}
	return NULL;
}

void asm_pass( asm_block_t* bk )
{
	bk->offs = 0;
	// printf( "Pass %i\n", bk->pass );
	asm_pass_t next_pass = bk->pass + 1;
	get_tok( &bk->ts );
	while ( bk->ts.tok[ 0 ] )
	{

		if ( bk->ts.c == ':' )
		{
			// printf( "Encountered label '%s'\n", bk->ts.tok );
			if ( bk->pass == PASS_LABEL )
			{
				lab_t label;
				label.name = _strdup( bk->ts.tok );
				label.offs = bk->offs;
				vec_push( bk->labels ) label;
			}
			else if ( bk->pass == PASS_ALIGN )
			{
				lab_t* label = find_label( bk, bk->ts.tok );
				if ( label->offs != bk->offs )
				{
					if ( bk->pass == PASS_ALIGN )
						next_pass = PASS_ALIGN;
					label->offs = bk->offs;
				}
			}
			// printf( "Set label offset to %llu\n", bk->offs );

			skip_c( &bk->ts );
			get_tok( &bk->ts );
		}
		else if ( bk->ts.tok[ 0 ] == '.' )
		{
			get_tok( &bk->ts );
			handle_directive( bk );
		}
		else if ( bk->ts.tok[ 0 ] == '#' )
		{
			do
			{
				skip_c( &bk->ts );
			} while ( bk->ts.c != '\n' && bk->ts.c != EOF );
		}
		else
		{
			// printf( "Supposed to be instruction %s, %c\n", bk->ts.tok,
			// bk->ts.c );
			backend_handle_ins( bk );
		}
	}
	// printf( "Finished %i pass, now on %i\n", bk->pass, next_pass );
	bk->pass = next_pass;
}

void assemble( const char* in_path, const char* out_path )
{
	asm_block_t bk;
	bk.ts = create_tok_stream( in_path );
	bk.pass = PASS_LABEL;
	bk.labels = vec_init( lab_t, uint16_t );
	fopen_s( &bk.out, out_path, "wb" );
	fflush( bk.out );

	do
	{
		asm_pass( &bk );
		rewind_tok_stream( &bk.ts );
	} while ( bk.pass != PASS_DONE );
	fclose( bk.out );

	close_tok_stream( &bk.ts );
	for ( size_t i = 0; i != bk.labels.size; ++i )
	{
		free( bk.labels.data[ i ].name );
	}
	free( bk.labels.data );
}

void put_bytes( asm_block_t* bk, const void* v, size_t n )
{
	if ( bk->pass == PASS_WRITE )
	{
		fwrite( v, 1, n, bk->out );
	}
	bk->offs += n;
}

void put_byte( asm_block_t* bk, const uint8_t v )
{
	if ( bk->pass == PASS_WRITE )
	{
		fputc( v, bk->out );
	}
	++bk->offs;
}

int64_t num_or_label( asm_block_t* bk )
{
	int64_t v;
	if ( isalpha( bk->ts.tok[ 0 ] ) )
	{
		if ( bk->pass == PASS_LABEL )
		{
			v = 0;
		}
		else
		{
			v = find_label( bk, bk->ts.tok )->offs;
		}
	}
	else
	{
		if ( bk->ts.tok[ 0 ] == '-' )
		{
			get_tok( &bk->ts );
			v = -strtoull( bk->ts.tok, NULL, 0 );
		}
		else
		{
			v = strtoull( bk->ts.tok, NULL, 0 );
		}
	}
	return v;  // TODO arithmetic
}

uint64_t unum_or_label( asm_block_t* bk )
{
	uint64_t v;
	if ( isalpha( bk->ts.tok[ 0 ] ) )
	{
		if ( bk->pass == PASS_LABEL )
		{
			v = 0;
		}
		else
		{
			v = find_label( bk, bk->ts.tok )->offs;
		}
	}
	else
	{
		v = strtoull( bk->ts.tok, NULL, 0 );
	}
	return v;  // TODO arithmetic
}

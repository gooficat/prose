#include "asm.h"
#include <stdio.h>
#include <string.h>
#include "tok.h"
#include "vec.h"

lab_t* find_label( asm_block_t* bk, const char* name )
{
	for ( size_t i = 0; i < bk->labels.size; ++i ) {
		if ( !strcmp( bk->labels.data[ i ].name, name ) ) {
			return &bk->labels.data[ i ];
		}
	}
	return NULL;
}

void handle_directive( asm_block_t* bk )
{
	printf( "Encountered directive '%s'\n", bk->ts.tok );
}

void asm_pass( asm_block_t* bk )
{
	bk->offs = 0;
	while ( bk->ts.c != EOF ) {
		get_tok( &bk->ts );

		if ( bk->ts.c == ':' ) {
			printf( "Encountered label '%s'\n", bk->ts.tok );
			if ( bk->pass == PASS_LABEL ) {
				lab_t label;
				label.name = _strdup( bk->ts.tok );
				label.offs = bk->offs;
				vec_push( bk->labels ) label;
			} else {
				lab_t* label = find_label( bk, bk->ts.tok );
				label->offs = bk->offs;
			}
			printf( "Set label offset to %llu\n", bk->offs );

			skip_c( &bk->ts );
			get_tok( &bk->ts );
		}

		if ( bk->ts.tok[ 0 ] == '.' ) {
			get_tok( &bk->ts );
			handle_directive( bk );
		}

		if ( bk->ts.tok[ 0 ] == '#' ) {
			do {
				skip_c( &bk->ts );
			} while ( bk->ts.c != '\n' && bk->ts.c != EOF );
		}

		// printf( "%s\t", bk->ts.tok );
	}
	// for debug
	++bk->pass;
}

void assemble( const char* in_path, const char* out_path )
{
	asm_block_t bk;
	bk.ts = create_tok_stream( in_path );
	bk.pass = PASS_LABEL;
	bk.labels = vec_init( lab_t, uint16_t );
	bk.offs = 0;
	fopen_s( &bk.out, out_path, "wb" );

	do {
		asm_pass( &bk );
	} while ( bk.pass != PASS_DONE );
	fclose( bk.out );
}

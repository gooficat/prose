#include <stdio.h>
#include <string.h>
#include "asm/asm.h"
#include "asm/backends/backends.h"
#include "lex.h"
#include "tok.h"
#include "vm/vm.h"

int main()
{
	set_backend( "6502" );
	assemble( "C:\\Users\\User\\Documents\\c\\prose\\prose\\fib.ps",
			  "C:\\Users\\User\\Documents\\c\\prose\\prose\\output.bin" );

	// tok_stream_t ts = create_tok_stream(
	// 	"C:\\Users\\User\\Documents\\c\\prose\\prose\\test.pr" );

	// token_t* tokens = read_tokens( &ts );

	// token_t* tok;
	// for ( tok = tokens; tok->type != TOK_EOF; ++tok ) {
	// 	if ( tok->type == TOK_IDT ) {
	// 		printf( "Identifier: %s\n", tok->sval );
	// 	} else if ( tok->type == TOK_LIT ) {
	// 		printf( "Literal: %llu\n", tok->uval );
	// 	} else {
	// 		printf( "Token type: %d\n", tok->type );
	// 	}
	// }
	// printf( "%llu tokens\n", tok - tokens );

	// prose_rom_t* rom;
	// prose_vm_t vm = init_prose_vm( 32 );
	// {
	// 	FILE* f;
	// 	fopen_s( &f, "C:\\Users\\User\\Documents\\c\\prose\\prose\\output.bin",
	// 			 "rb" );
	// 	fseek( f, 0, SEEK_END );
	// 	uint64_t program_len = ftell( f );
	// 	rom = malloc( sizeof( prose_rom_t ) + program_len );
	// 	rom->entry = 0;
	// 	rom->size = program_len;
	// 	fseek( f, 0l, SEEK_SET );
	// 	fread( rom->data, 1llu, rom->size, f );
	// 	fclose( f );
	// }
	// prose_load_rom( &vm, rom );
	// prose_execute( &vm );

	// free( rom );
	// delete_prose_vm( &vm );
}

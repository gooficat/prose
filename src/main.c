#include <string.h>
#include "asm/asm.h"
#include "lex.h"
#include "tok.h"
#include "vm/vm.h"

int main()
{
	// assemble( "C:\\Users\\User\\Documents\\c\\prose\\prose\\test.ps",
	// 		  "C:\\Users\\User\\Documents\\c\\prose\\prose\\output.bin" );

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
	prose_rom_t* rom;
	prose_vm_t vm = init_prose_vm( 8 );
	{
		uint8_t program[] = {
			PROSE_PSH_IMM, 0x01, 0x00, 0x00,		  0x00,
			0x00,		   0x00, 0x00, 0x00,		  PROSE_PSH_IMM,
			0x0A,		   0x00, 0x00, 0x00,		  0x00,
			0x00,		   0x00, 0x00, PROSE_ADD_TOP, PROSE_HLT_CPU,
		};
		rom = malloc( sizeof( prose_rom_t ) + sizeof( program ) );
		rom->entry = 0;
		rom->size = sizeof( program );
		memcpy( rom->data, program, rom->size );
	}
	prose_load_rom( &vm, rom );
	prose_execute( &vm );

	free( rom );
	delete_prose_vm( &vm );
}

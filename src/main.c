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

	prose_vm_t vm = init_prose_vm( 1024 );
	prose_rom_t* rom = malloc( sizeof( prose_rom_t ) + 8 );
	{
		rom->entry = 0;
		rom->size = 8;
		memcpy(	 //
			rom->data,
			&(uint8_t[]){
				PROSE_HLT_CPU,
			},
			8  //
		);
	}
	prose_load_rom( &vm, rom );
	prose_execute( &vm );

	free( rom );
	delete_prose_vm( &vm );
}

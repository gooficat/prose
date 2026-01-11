#include "lex.h"
#include "tok.h"

int main()
{
	tok_stream_t ts = create_tok_stream(
		"C:\\Users\\User\\Documents\\c\\prose\\prose\\test.pr" );

	token_t* tokens = read_tokens( &ts );

	token_t* tok;
	for ( tok = tokens; tok->type != TOK_EOF; ++tok ) {
		if ( tok->type == TOK_IDT ) {
			printf( "Identifier: %s\n", tok->sval );
		} else if ( tok->type == TOK_LIT ) {
			printf( "Literal: %llu\n", tok->uval );
		} else {
			printf( "Token type: %d\n", tok->type );
		}
	}
	printf( "%llu tokens\n", tok - tokens );
}

#include "lex.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

token_t* read_tokens( tok_stream_t* ts )
{
	token_t* out = malloc( sizeof( token_t ) );
	unsigned long long num_tok = 0, tok_cap = 1;

	while ( ts->c != EOF ) {
		token_t tk;
		get_tok( ts );

		if ( isalpha( ts->tok[ 0 ] ) ) {
			tk.type = TOK_IDT;
			tk.sval = _strdup( ts->tok );
		} else if ( isdigit( ts->tok[ 0 ] ) ) {
			tk.type = TOK_LIT;
			tk.uval = strtoull( ts->tok, NULL, 0 );
		} else {
			tk.type = (tok_type_t)ts->tok[ 0 ];
		}
		if ( num_tok >= tok_cap ) {
			tok_cap *= 2;
			out = realloc( out, sizeof( token_t ) * tok_cap );
		}
		out[ num_tok++ ] = tk;
		printf( "Token %s\n", ts->tok );
	}
	out = realloc( out, sizeof( token_t ) * num_tok + sizeof( tok_type_t ) );
	( (tok_type_t*)( &out[ num_tok ] ) )[ 0 ] = TOK_EOF;

	return out;
}

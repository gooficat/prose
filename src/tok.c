#include "tok.h"
#include <ctype.h>

tok_stream_t create_tok_stream( const char* path )
{
	tok_stream_t ts;
	fopen_s( &ts.f, path, "r" );
	ts.c = fgetc( ts.f );
	return ts;
}

void get_tok( tok_stream_t* ts )
{
	while ( isspace( ts->c ) ) {
		ts->c = fgetc( ts->f );
	}

	if ( isalnum( ts->c ) ) {
		unsigned char i = 0;
		do {
			ts->tok[ i++ ] = ts->c;
			ts->c = fgetc( ts->f );
		} while ( isalnum( ts->c ) );
		ts->tok[ i ] = '\0';
	} else if ( ts->c != EOF ) {
		ts->tok[ 0 ] = ts->c;
		ts->tok[ 1 ] = '\0';
		ts->c = fgetc( ts->f );
	} else
		ts->tok[ 0 ] = '\0';
}

void skip_c( tok_stream_t* ts )
{
	ts->c = fgetc( ts->f );
}

void skip_wsp( tok_stream_t* ts )
{
	while ( isspace( ts->c ) ) {
		ts->c = getc( ts->f );
	}
}

void close_tok_stream( tok_stream_t* ts )
{
	fclose( ts->f );
}

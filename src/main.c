#include "mem.h"
#include "tok.h"
#include <stdio.h>

int main()
{
	tok_stream_t stream = create_tok_stream("../prose/test.psm");

	fetch_token_file(&stream);

	// while ()
	printf("%s\n", stream.token);
	//
}
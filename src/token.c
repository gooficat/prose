#include "token.h"

#include <ctype.h>

TokenStream MakeStream(const char *path)
{
	TokenStream out;
	init_stream(out.stream, path);
	out.token = create_vector(char, u8);
	NextToken(&out);
	return out;
}

void NextToken(TokenStream *stream)
{
	stream->token.size = 0;
	if (stream->stream.buffer == EOF)
	{
		return;
	}
	while (isspace(stream->stream.buffer))
	{
		fsgetc(stream->stream);
		if (stream->stream.buffer == EOF)
		{
			return;
		}
	}

	do
	{
		push(stream->token, stream->stream.buffer);
		fsgetc(stream->stream);
	} while (isalnum(stream->stream.buffer));
}
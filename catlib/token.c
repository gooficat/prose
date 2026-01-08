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
	push(stream->token, 0);
}

u64 UintFromToken(Token *token)
{
	i8 radix;
	char *s = token->data;

	if (token->size > 2)
	{
		switch (token->data[1])
		{
		case 'x':
			radix = 16;
			break;
		case 'o':
			radix = 8;
			break;
		case 'b':
			radix = 2;
			break;
		default:
			goto decimal;
		}
	}
	else
	{
	decimal:;
		radix = 10;
	}

	return strtoull(token->data, NULL, radix);
}

GenericIntegral NumberFromToken(Token *token)
{
	GenericIntegral out;

	if (token->size > 2 && isalpha(token->data[1]))
	{
		out.type = INTEGRAL_UINT;
		out.u = UintFromToken(token);
	}

	switch (token->data[token->size - 1])
	{
	case 'f':
		out.type = INTEGRAL_FLOAT;
		out.f = strtod(token->data, NULL);
		break;
	case 'u':
		out.type = INTEGRAL_UINT;
		out.u = strtoull(token->data, NULL, 10);
		break;
	default:
		out.type = INTEGRAL_INT;
		out.i = strtoll(token->data, NULL, 10);
		break;
	}
	return out;
}

bool IsOperator(char c)
{
	switch (c)
	{
	case '+':
	case '-':
	case '/':
	case '*':
	case '%':
	case '&':
	case '^':
	case '|':
		return true;
	default:
		return false;
	}
}

i8 TokenCmp(const Token *a, const Token *b)
{
	return a->size == b->size && memcmp(a->data, b->data, a->size);
}
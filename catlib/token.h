#pragma once

#include <ctype.h>

#include "class.h"
#include "string.h"

#include "types.h"
#include "vector.h"

#include "fstream.h"

vec_type(char, u8);

typedef vector_char_u8 Token;

class(TokenStream)
{
	Token token;
	FStream stream;
};

TokenStream MakeStream(const char *path);

void NextToken(TokenStream *stream);
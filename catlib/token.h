#pragma once

#include <ctype.h>

#include "class.h"
#include "string.h"

#include "token.h"
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

enum(IntegralType, u8){
	INTEGRAL_FLOAT,
	INTEGRAL_INT,
	INTEGRAL_UINT,
};

class(GenericIntegral)
{
	IntegralType type;
	union {
		u64 u;
		i64 i;
		f64 f;
	};
};

GenericIntegral NumberFromToken(Token *token);

u64 UintFromToken(Token *token);

bool IsOperator(char c);

i8 TokenCmp(const Token *a, const Token *b);
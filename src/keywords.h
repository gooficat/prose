#pragma once

#include "class.h"
#include "types.h"

enum(Keyword, u8){
	KEYWORD_LET,
	KEYWORD_MUT,
	KEYWORD_RET,
	KEYWORD_BRK,
	KEYWORD_CNT,
};

extern const char *keywords[];

i8 FindKeyword(const char *s);
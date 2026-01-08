#include "keywords.h"
#include <string.h>

const char *keywords[] = {
	"let",
	"mut",
	"return",
	"break",
	"continue",
};
#define num_kws sizeof(keywords) / sizeof(const char *)

i8 FindKeyword(const char *s)
{
	for (i8 i = 0; i != num_kws; ++i)
	{
		if (!strcmp(s, keywords[i]))
		{
			return i;
		}
	}
	return -1;
}


#include "token.h"

int main(void)
{
	TokenStream stream = MakeStream("../tests/hello.prose");

	while (stream.token.size)
	{
		printf("'%.*s'\n", stream.token.size, stream.token.data);
		NextToken(&stream);
	}

	return 0;
}

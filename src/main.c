
#include "ast.h"
#include "fstream.h"
#include "tree_walk.h"
#include <token.h>

int main(void)
{
	TokenStream stream = MakeStream("../tests/hello.prose");

	// while (stream.token.size)
	// {
	// 	printf("'%.*s'\n", stream.token.size, stream.token.data);
	// 	NextToken(&stream);
	// }

	// rewind_stream(stream.stream);

	ASTRoot root = GenTree(&stream);

	// PrintTree(root);

	return 0;
}

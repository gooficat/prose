#include "ast.h"
#include "mem.h"

ast_block_t gen_tree( tok_stream_t* ts )
{
	ast_block_t bk;
	bk.mt = create_mem_tracker();

	return bk;
}

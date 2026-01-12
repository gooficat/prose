#include "ast.h"
#include "mem.h"

ast_block_t gen_tree( tok_stream_t* ts )
{
	ast_block_t bk = {
		.mt = create_mem_tracker(),
		.root = {
			.type = AST_NODE_SCOP,
			.scope = {
				.parent = NULL,
				.nodes = {
					.data = tracked_malloc ( &bk.mt, sizeof ( past_node_t ) ),
					.size = 0,
					.cap = 1,
				},
				.vars =  {
					.data = tracked_malloc ( &bk.mt, sizeof ( ast_var_def_t ) ),
					.size = 0,
					.cap = 1,
				},
			},
		},
	};

	return bk;
}

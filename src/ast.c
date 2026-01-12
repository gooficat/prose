#include "ast.h"
#include <string.h>
#include "mem.h"
#include "tok.h"

uint8_t get_var_type( ast_block_t* bk, ast_node_scope_t* scope,
					  tok_stream_t* ts )
{
	return 1;  // placeholder
}

ast_var_def_t gen_var_def( ast_block_t* bk, ast_node_scope_t* scope,
						   tok_stream_t* ts )
{
	ast_var_def_t var;
	var.type = get_var_type( bk, scope, ts );
	get_tok( ts );

	var.name = tracked_strdup( &bk->mt, ts->tok );

	return var;
}

ast_node_t ast_gen_func( ast_block_t* bk, ast_node_scope_t* scope,
						 tok_stream_t* ts )
{
	ast_node_func_def_t func;

	uint8_t len = strlen( ts->tok ) + 1;
	func.name = tracked_strdup( &bk->mt, ts->tok );

	return (ast_node_t){
		.type = AST_NODE_FDEF,
		.func_def = func,
	};
}

void ast_gen_scope( ast_block_t* bk, ast_node_scope_t* scope, tok_stream_t* ts )
{
	while ( ts->c != EOF )
	{
		get_tok( ts );

		if ( !strcmp( ts->tok, "fn" ) )
		{
			get_tok( ts );
			vec_push( scope->nodes ) ast_gen_func( bk, scope, ts );
		}

		printf( "%s\n", ts->tok );
	}
}

ast_block_t gen_tree( tok_stream_t* ts )
{
	ast_block_t bk;
	bk.mt = create_mem_tracker();
	bk.root = (ast_node_t){
		.type = AST_NODE_SCOP,
		.scope = {
			.parent = NULL,
			.nodes = {
				.data = tracked_malloc ( &bk.mt, sizeof ( ast_node_t ) ),
				.size = 0,
				.cap = 1,
			},
			.vars =  {
				.data = tracked_malloc ( &bk.mt, sizeof ( ast_var_def_t ) ),
				.size = 0,
				.cap = 1,
			},
		},
	};

	ast_gen_scope( &bk, &bk.root.scope, ts );

	return bk;
}

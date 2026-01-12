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
	get_tok( ts );

	printf( "Variable named %s\n", var.name );

	return var;
}

ast_node_scope_t ast_gen_scope( ast_block_t* bk, tok_stream_t* ts,
								ast_node_scope_t* parent );

ast_node_t ast_gen_func( ast_block_t* bk, ast_node_scope_t* scope,
						 tok_stream_t* ts )
{
	ast_node_func_def_t func;
	func.args = tracked_vec_init( bk->mt, ast_var_def_t, uint8_t );

	func.name = tracked_strdup( &bk->mt, ts->tok );
	get_tok( ts );
	while ( ts->tok[ 0 ] != ')' )
	{
		get_tok( ts );
		vec_push( func.args ) gen_var_def( bk, scope, ts );
	}
	get_tok( ts );

	printf( "Function %s with %hu args\n", func.name, func.args.size );

	func.body = ast_gen_scope( bk, ts, scope );

	return (ast_node_t){
		.type = AST_NODE_FDEF,
		.func_def = func,
	};
}

ast_node_scope_t ast_gen_scope( ast_block_t* bk, tok_stream_t* ts,
								ast_node_scope_t* parent )
{
	ast_node_scope_t scope = {
		.nodes = tracked_vec_init( bk->mt, ast_node_t, uint16_t ),
		.vars = tracked_vec_init( bk->mt, ast_var_def_t, uint8_t ),
		.parent = parent,
	};

	get_tok( ts );
	while ( ts->tok[ 0 ] != '}' && ts->c != EOF )
	{
		if ( !strcmp( ts->tok, "fn" ) )
		{
			get_tok( ts );
			vec_push( scope.nodes ) ast_gen_func( bk, &scope, ts );
		}
		else if ( !strcmp( ts->tok, "return" ) )
		{
			printf( "Return " );
			get_tok( ts );
			printf( "%s\n", ts->tok );
			get_tok( ts );
			get_tok( ts );
		}
		else
		{
			printf( "'%s'\n", ts->tok );
			get_tok( ts );
		}
	}
	return scope;
}

ast_block_t gen_tree( tok_stream_t* ts )
{
	ast_block_t bk;
	bk.mt = create_mem_tracker();

	bk.root.type = AST_NODE_SCOP;
	bk.root.scope = ast_gen_scope( &bk, ts, NULL );

	return bk;
}

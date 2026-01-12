#include "ast.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "tok.h"

bool is_operator( char c )
{
	switch ( c )
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '|':
	case '%':
	case '^':
		return true;
	default:
		return false;
	}
}

const char* orders[] = {
	"continue",
	"break",
	"return",
	"goto",
};

ast_var_def_t* ast_find_var( ast_node_scope_t* scope, tok_stream_t* ts )
{
	for ( uint16_t i = 0; i != scope->vars.size; ++i )
	{
		if ( !strcmp( scope->vars.data[ i ].name, ts->tok ) )
		{
			return &scope->vars.data[ i ];
		}
	}
	if ( scope->parent )
	{
		return ast_find_var( scope->parent, ts );
	}
	else
	{
		return NULL;
	}
	get_tok( ts );
}

ast_node_t gen_singular( ast_block_t* bk, ast_node_scope_t* scope,
						 tok_stream_t* ts )
{
	ast_node_t node;
	if ( isdigit( ts->tok[ 0 ] ) )
	{
		node.type = AST_NODE_LITR;
		if ( strchr( ts->tok, '.' ) )
		{
			node.literal.type = AST_LIT_FLT;
			node.literal.fval = strtod( ts->tok, NULL );
		}
		else
		{
			node.literal.type = AST_LIT_INT;
			node.literal.ival = strtoll( ts->tok, NULL, 0 );
		}
		get_tok( ts );
	}
	else
	{
		skip_wsp( ts );
		if ( ts->c == '(' )
		{
			node.type = AST_NODE_FCAL;
			node.func_call.args =
				tracked_vec_init( bk->mt, ast_node_t, uint16_t );
			node.func_call.name = tracked_strdup( &bk->mt, ts->tok );
			get_tok( ts );
			while ( ts->tok[ 0 ] != ')' )
			{
				get_tok( ts );
				vec_push( node.func_call.args ) gen_singular( bk, scope, ts );
			}
			get_tok( ts );
			printf( "Func call %hu args\n", node.func_call.args.size );
		}
	}
	if ( is_operator( ts->tok[ 0 ] ) )
	{
		ast_node_operation_t opn;
		opn.operator= ts->tok[ 0 ];

		opn.left = tracked_memdup( &bk->mt, &node, sizeof( node ) );

		ast_node_t right = gen_singular( bk, scope, ts );
		opn.right = tracked_memdup( &bk->mt, &right, sizeof( right ) );
		return (ast_node_t){
			.type = AST_NODE_MATH,
			.operation = opn,
		};
	}
	else
	{
		return node;
	}
}

ast_node_t ast_gen_expr( ast_block_t* bk, ast_node_scope_t* scope,
						 tok_stream_t* ts )
{
	ast_node_t out;

	out = gen_singular( bk, scope, ts );

	if ( ts->tok[ 0 ] == '=' )
	{
		out.type = AST_NODE_SETV;
		ast_node_assignment_t assign;
		assign.to_what = tracked_memdup( &bk->mt, &out, sizeof( out ) );
		get_tok( ts );
		out = gen_singular( bk, scope, ts );
		assign.value = tracked_memdup( &bk->mt, &out, sizeof( out ) );
		out.assignment = assign;
	}

	return out;
}

ast_node_order_t ast_gen_order( ast_block_t* bk, ast_node_scope_t* scope,
								tok_stream_t* ts )
{
	ast_node_order_t order;
	order.type = ORDER_TYPE_NONE;
	for ( int8_t i = 0; i != sizeof( orders ) / sizeof( orders[ 0 ] ); ++i )
	{
		if ( !strcmp( ts->tok, orders[ i ] ) )
		{
			order.type = i;
		}
	}
	if ( order.type != ORDER_TYPE_NONE )
	{
		get_tok( ts );

		ast_node_t oval = gen_singular( bk, scope, ts );

		order.value = tracked_memdup( &bk->mt, &oval, sizeof( ast_node_t ) );
	}
	return order;
}

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

	func.return_type = get_var_type( bk, scope, ts );

	get_tok( ts );

	printf( "Function %s with %hu args, returning type %hhu\n", func.name,
			func.args.size, func.return_type );

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
		else
		{
			ast_node_order_t order = ast_gen_order( bk, &scope, ts );
			if ( order.type != ORDER_TYPE_NONE )
			{
				vec_push( scope.nodes )( ast_node_t ){
					.type = AST_NODE_ORDR,
					.order = order,
				};
				printf( "Order type %i, rval type %i\n", order.type,
						order.value->type );
			}
			else if ( ts->tok[ 0 ] != ';' )
			{
				vec_push( scope.nodes ) ast_gen_expr( bk, &scope, ts );
			}
			else
			{
				get_tok( ts );
			}
			// ast_node_t rval = gen_singular( bk, &scope, ts );
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

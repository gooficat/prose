#pragma once

#include <stdint.h>
#include "mem.h"
#include "tok.h"
typedef enum
{
	AST_NODE_NONE,
	AST_NODE_SCOP,
	AST_NODE_FDEF,
	AST_NODE_FCAL,
	AST_NODE_VDEF,
	AST_NODE_VREF,
	AST_NODE_SETV,
	AST_NODE_COND,
	AST_NODE_MATH,
	AST_NODE_ILIT,
	AST_NODE_CLIT,
	AST_NODE_SLIT,
	AST_NODE_ORDR,
} ast_node_type_t;

typedef struct ast_node ast_node_t;

typedef struct
{
	char* name;
	uint8_t type;
	bool is_static;
	bool is_const;
} ast_var_def_t;

typedef struct
{
	ast_node_t* left;
	char operator;
	ast_node_t* right;
} ast_node_operation_t;

typedef struct
{
	ast_var_def_t* to_what;
	ast_node_t* value;
} ast_node_assignment_t;

typedef struct
{
	ast_var_def_t* to_what;
} ast_node_var_ref_t;

typedef enum
{
	ORDER_TYPE_NONE,
	ORDER_TYPE_CONT,
	ORDER_TYPE_BREK,
	ORDER_TYPE_RTRN,
	ORDER_TYPE_GOTO,
} order_type_t;

typedef struct
{
	order_type_t type;
	ast_node_t* value;
} ast_node_order_t;

vec_type( ast_node_t, uint16_t );
vec_type( ast_var_def_t, uint8_t );

typedef struct ast_node_scope
{
	ast_node_t* parent;
	vec_ast_node_t_uint16_t nodes;
	vec_ast_var_def_t_uint8_t vars;
} ast_node_scope_t;

typedef struct ast_node_func_def
{
	char* name;
	vec_ast_var_def_t_uint8_t args;
	ast_node_scope_t body;
} ast_node_func_def_t;

struct ast_node
{
	ast_node_type_t type;
	union
	{
		ast_node_operation_t operation;
		ast_node_assignment_t assignment;
		ast_node_var_ref_t var_ref;
		ast_node_order_t order;
		ast_node_scope_t scope;
		ast_node_func_def_t func_def;
	};
};

typedef struct
{
	ast_node_t root;
	mem_tracker_t mt;
} ast_block_t;

ast_block_t gen_tree( tok_stream_t* ts );

#pragma once

#include <stdint.h>
#include "mem.h"
#include "tok.h"
typedef enum
{
	AST_NODE_NONE,
	AST_NODE_ROOT,
	AST_NODE_SCOP,
	AST_NODE_FDEF,
	AST_NODE_FCALL,
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
	ast_node_t* left;
	char operator;
	ast_node_t* right;
} ast_node_operation_t;

typedef struct
{
} ast_node_assignment_t;
typedef struct
{
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

struct ast_node
{
	ast_node_type_t type;
	union
	{
		ast_node_operation_t operation;
		ast_node_assignment_t assignment;
		ast_node_var_ref_t var_ref;
		ast_node_order_t order;
	};
};

typedef struct
{
	ast_node_t root;
	mem_tracker_t mt;
} ast_block_t;

ast_block_t gen_tree( tok_stream_t* ts );

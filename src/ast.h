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
} ast_node_type_t;

typedef struct
{
	ast_node_type_t type;
} ast_node_t;

typedef struct
{
	ast_node_t root;
	mem_tracker_t mt;
} ast_block_t;

ast_block_t gen_tree( tok_stream_t* ts );

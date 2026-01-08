#pragma once

/**
 *
 *
 *            __..--''``---....___   _..._    __
 *        _.-'    .-/";  `        ``<._  ``.''_ `.
 *    _.-' _..--.'     \                    `( ) )
 *   (_..-'    (        ;_..__               ; `'
 *             `-._,_)'      ``--...____..-'
 */

#include <class.h>
#include <types.h>

#include <token.h>
#include <vector.h>

enum(ASTNodeType, u8){
	AST_FN_CALL,
	AST_FN_DEF,
	AST_DEFINE,
	AST_ASSIGN,
	AST_OPERATION,
};

class(ASTVarDef)
{
	Token name;
	// word-only for now
};

vec_type(ASTVarDef, u16);

class(ASTFnDef)
{
	char *name;
	struct ASTNode *body;
	vector_ASTVarDef_u16 vars;
};

class(ASTOperation)
{
	struct ASTNode *base;
};

class(ASTAssignment)
{
	ASTVarDef *to_what;
	struct ASTNode *value;
};

class(ASTNode)
{
	u8 type;
	union {
		ASTFnDef fn_def;
		ASTAssignment assignment;
	};
};

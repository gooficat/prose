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
	AST_FN_DEF,
	AST_DEFINE,
	AST_ASSIGN,
	AST_OPERATION,
	AST_SCOPE,
	AST_SINGULAR,
};

typedef struct ASTNode *pASTNode;

class(ASTVarDef)
{
	Token name;
	// word-only for now
};

vec_type(ASTVarDef, u16);
vec_type(pASTNode, u16);

class(ASTScope)
{
	vector_pASTNode_u16 contents;
	vector_ASTVarDef_u16 vars;

	struct ASTScope *parent;
};

class(ASTFnDef)
{
	Token name;
	ASTScope body;
};

class(ASTOperational)
{
	char operation;
	pASTNode base;
};

vec_type(ASTOperational, u8);

class(ASTOperation)
{
	pASTNode base;
	vector_ASTOperational_u8 operands;
};

class(ASTAssignment)
{
	ASTVarDef *to_what;
	struct ASTNode *value;
};

class(ASTRoot)
{
	struct ASTScope body;
};

vec_type(pASTNode, u8);

class(ASTFnCall)
{
	ASTFnDef *to_what;
	vector_pASTNode_u8 args;
};

enum(ASTSingularType, u8){
	AST_SINGULAR_VAR,
	AST_SINGULAR_LIT,
	AST_SINGULAR_FN_CALL,
};

enum(ASTRefType, u8){
	AST_REF_DEREFERENCE,
	AST_REF_ADDRESS,
};

class(ASTVarRef)
{
	ASTVarDef *to_what;
};

class(ASTSingular)
{
	ASTSingularType type;
	ASTRefType ref_type;
	union {
		GenericIntegral literal;
		ASTVarRef var_ref;
		ASTFnCall fn_call;
	};
};

class(ASTNode)
{
	u8 type;
	union {
		ASTScope scope;
		ASTFnDef fn_def;
		ASTAssignment assignment;
		ASTSingular singular;
		ASTOperation operation;
	};
};

ASTRoot GenTree(TokenStream *stream);
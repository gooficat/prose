#include "tree_walk.h"
#include "ast.h"
#include <stdio.h>

static char global_indent[8] = {0};
#define up_indent(amt)                                                                                                 \
	{                                                                                                                  \
		u8 l = strlen(global_indent) + amt - 1;                                                                        \
		global_indent[l] = '\t';                                                                                       \
		global_indent[l + 1] = 0;                                                                                      \
	}
#define down_indent(amt) global_indent[strlen(global_indent) - amt] = 0;

void PrintScope(const ASTScope scope);

void PrintNode(const ASTNode node)
{
	switch (node.type)
	{
	case AST_ASSIGN:
		printf("Assignment to %.*s:\n", node.assignment.to_what->name.size, node.assignment.to_what->name.data);
		up_indent(1);
		PrintNode(*node.assignment.value);
		down_indent(1);
		break;
	case AST_FN_DEF:
		printf("Function definition named %.*s\n", node.fn_def.name.size, node.fn_def.name.data);
		up_indent(1);
	case AST_SCOPE:
		PrintScope(node.scope);
		break;
	}
}

void PrintScope(const ASTScope scope)
{
	printf("Encountered a scope...\n");

	up_indent(1);

	printf("Scope contains variables:\n");
	for (u16 i = 0; i != scope.vars.size; ++i)
	{
		printf("%s%.*s\n", global_indent, scope.vars.data[i].name.size, scope.vars.data[i].name.data);
	}
	down_indent(1);
	printf("Contents of scope:\n");
	up_indent(1);

	for (u16 i = 0; i != scope.contents.size; ++i)
	{
		PrintNode(*scope.contents.data[i]);
	}
}

void PrintTree(const ASTRoot root)
{

	printf("Printing AST tree.\n");

	PrintScope(root.body);
}
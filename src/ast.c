#include "ast.h"
#include "token.h"
#include "vector.h"

/*
		,.                 .,
		,: ':.    .,.    .:' :,
		,',   '.:'   ':.'   ,',
		: '.  '         '  .' :
		', : '           ' : ,'
		'.'               '.'
		 ,:                 :,
		,:                   :,
		,:                   :,
		 ,:                 :,
		  ,: ,     :     , :,
		   :' ',.,' ',.,:' ':
		  :'      ':WW::'   '.
		 .:'       '::::'   ':
		 ,:        '::::'    :,
		 :'         ':::'    ':
		,:           ':''     :.
	   .:'             '.     ',.
	  ,:'               ''     '.
	  .:'               .',    ':
	 .:'               .'.,     :
	 .:                .,''     :
	 ::                .,''    ,:
	 ::              .,'','   .:'
   .,::'.           .,','     ::::.
 .:'     ',.       ,:,       ,WWWWW,
 :'        :       :W:'     :WWWWWWW,          .,.
 :         ',      WWW      WWWWWWWWW          '::,
 '.         ',     WWW     :WWWWWWWWW            '::,
  '.         :     WWW     :WWWWWWWW'             :::
   '.       ,:     WWW     :WWWWWWW'             .:::
	'.     .W:     WWW     :WWWWWW'           .,:::'
	 '.   :WW:     WWW     :WWWWW'      .,,:::::''
	.,'   ''::     :W:     :WWWWW.  .,::::''
 ,'        ''','',',','','''WWWWW::::''
  ':,,,,,,,':  :  : : :  :  :WWWW'''
*/

ASTVarDef *FindVar(TokenStream *stream, ASTScope *scope)
{
	ASTVarDef *var = NULL;
	for (u16 i = 0; i != scope->vars.size; ++i)
	{
		if (scope->vars.data[i].name.size == stream->token.size &&
			!memcmp(scope->vars.data[i].name.data, stream->token.data, stream->token.size))
		{
			var = &scope->vars.data[i];
			break;
		}
	}
	if (!var)
	{
		if (scope->parent)
		{
			var = FindVar(stream, scope->parent);
		}
	}
	return var;
}

ASTSingular GenSingular(TokenStream *stream, ASTScope *scope)
{
	//
}

ASTNode GenRValue(TokenStream *stream, ASTScope *scope)
{
}

void GenVarDef(TokenStream *stream, ASTScope *scope)
{
	NextToken(stream);
	ASTVarDef *var = FindVar(stream, scope);

	ASTVarDef new_var;
	new_var.name = stream->token; // more convenient than regular copy
	stream->token = create_vector(char, u8);
	push(scope->vars, new_var);
	var = &scope->vars.data[scope->vars.size - 1];

	NextToken(stream);
}

bool GenOrder(TokenStream *stream, ASTScope *parent)
{
	ASTNode out;
	out.type = 0;

	return false;
}

ASTScope GenScope(TokenStream *stream, ASTScope *parent)
{
	ASTScope out;
	out.parent = parent;

	out.vars = create_vector(ASTVarDef, u16);

	out.contents = create_vector(pASTNode, u16);

	while (stream->token.size && stream->token.data[0] != '}')
	{
		printf("Token %.*s\n", stream->token.size, stream->token.data);

		NextToken(stream);
	}

	return out;
}

ASTRoot GenTree(TokenStream *stream)
{
	ASTRoot out;
	out.body = GenScope(stream, NULL);
	return out;
}
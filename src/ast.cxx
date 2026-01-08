#include "ast.hxx"
#include "token.hxx"
#include <iostream>

namespace AST
{

std::unordered_map<std::string, Type> Type::BuiltInTypes = {
	{
		"u8",
		{
			TypeSize::Byte,
			false,
		},
	},
	{
		"u16",
		{
			TypeSize::Word,
			false,
		},
	},
	{
		"u32",
		{
			TypeSize::DWord,
			false,
		},
	},
	{
		"u64",
		{
			TypeSize::QWord,
			false,
		},
	},
	{
		"i8",
		{
			TypeSize::Byte,
			true,
		},
	},
	{
		"i16",
		{
			TypeSize::Word,
			true,
		},
	},
	{
		"i32",
		{
			TypeSize::DWord,
			true,
		},
	},
	{
		"i64",
		{
			TypeSize::QWord,
			true,
		},
	},

};

Var::Var(Token::Stream &stream)
{
	this->constant = !stream.NextIfMatch("const");
	this->references = stream.NextIfMatch("&");

	this->name = stream.GetToken();
	stream.NextToken();

	if (stream.NextIfMatch(":"))
	{
		this->type = &Type::BuiltInTypes.at(stream.GetToken());
		stream.NextToken();
	}

	std::cout << (constant ? "Imm" : "M") << "utable of name " << name << " and type sized " << (int)type->size
			  << ".\n";
}

Function::Function(Token::Stream &stream)
{
	name = stream.GetToken();

	stream.NextToken();
	while (stream.GetToken() != ")")
	{
	}

	Scope::Generate(stream);
}

void Scope::Generate(Token::Stream &stream)
{
	while (stream.GetToken().size())
	{
		// std::cout << stream.GetToken() << "\t";

		if (stream.NextIfMatch("let"))
		{
			vars.emplace_back(stream);
		}
		else if (stream.NextIfMatch("fn"))
		{
			nodes.emplace_back(new Function(stream));
		}

		stream.NextToken();
	}
}

void Root::Generate(Token::Stream &stream)
{
	std::cout << "Generating AST\n";
	stream.NextToken();

	Scope::Generate(stream);
}

Root::Root()
{
	parent = nullptr;
}

} // namespace AST
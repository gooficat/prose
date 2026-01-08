#pragma once

#include "token.hxx"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace AST
{

enum class TypeSize : uint8_t
{
	Byte = 1,
	Word = 2,
	DWord = 4,
	QWord = 8,
	OWord = 16,
};
struct Type
{
	TypeSize size;
	bool is_signed;
	static std::unordered_map<std::string, Type> BuiltInTypes;
};

struct Node
{
};

struct LValue : Node
{
};

struct RValue : Node
{
};

struct Operand
{
	char operation;
	std::unique_ptr<RValue> value;
};

struct Operation : RValue
{
	std::unique_ptr<RValue> left;
	std::vector<Operand> operands;
};

struct Literal : RValue
{
	~Literal() = delete;
	enum class LiteralType
	{
		UNSIGNED,
		SIGNED,
		STRING,
	} type;
	union LiteralValues {
		~LiteralValues() = delete;
		uintmax_t u;
		intmax_t i;
		std::string s;
	} value;
};

struct Var
{
	Var(Token::Stream &stream);
	std::string name;
	Type *type;
	bool references;
	bool constant;
};

struct VarRef : LValue, RValue
{
	Var *to_what;
};

struct Scope : Node
{
	void Generate(Token::Stream &stream);
	std::vector<std::unique_ptr<Node>> nodes;
	std::vector<Var> vars;
	Scope *parent;
};

struct Function : Scope
{
	std::string name;

	Function(Token::Stream &stream);
};

struct Root : Scope
{
	Root();
	void Generate(Token::Stream &stream);
};

}; // namespace AST
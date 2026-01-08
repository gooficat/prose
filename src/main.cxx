#include "ast.hxx"
#include "token.hxx"

int main(void)
{
	Token::Stream stream(R"(C:\Users\User\Documents\c\prose\tests\test.prose)");

	AST::Root root;
	root.Generate(stream);
}

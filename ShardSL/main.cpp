#include <iostream>
#include "src/Lexer.h"
#include "src\Parser.h"
#include "src\ASTPrintVisitor.h"

int main(void)
{
	const char* str =
		R"(
		main : (foo : float32, bar : Mat4[][]) -> uint8
		{
		}
		)";

	Lexer lex;
	TokenList tokens = lex.Tokenize(str);
	Parser par;
	NodeList nodes = par.Parse(tokens);

	ASTPrintVisitor vis;

	for (Node* n : nodes)
	{
		vis.Visit(n);
	}

	system("PAUSE");
	return 0;
}
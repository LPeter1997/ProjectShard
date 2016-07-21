#pragma once

#include <map>
#include "Lexer.h"
#include "Types.h"
#include "AST.h"

struct OpDesc
{
	uint Precedence;
	bool RightAssoc;
};

class Parser
{
private:
	TokenList m_Tokens;
	Token m_Current;
	uint m_Index;
	uint m_Mark;
	std::map<TokenType, OpDesc> m_Precedence;

public:
	Parser();
	~Parser();

private:
	void Next();
	void Mark();
	void Rollback();

	NodeList ParseProgram();

	Node* ParseFnDef();
	std::vector<Node*> ParseParameterList();
	Node* ParseParameter();
	Node* ParseType();
	NodeList ParseStatementList();
	Node* ParseStatement();
	Node* ParseVarDecl();
	Node* ParseExpression();
	Node* ParseValue();

public:
	NodeList Parse(const TokenList& tokens);
};
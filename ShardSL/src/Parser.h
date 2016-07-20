#pragma once

#include "Lexer.h"
#include "Types.h"
#include "AST.h"

class Parser
{
private:
	TokenList m_Tokens;
	Token m_Current;
	uint m_Index;
	uint m_Mark;

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

public:
	NodeList Parse(const TokenList& tokens);
};
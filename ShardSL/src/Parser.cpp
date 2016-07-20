#include <iostream>
#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::Next()
{
	m_Current = m_Tokens[m_Index++];
}

void Parser::Mark()
{
	m_Mark = m_Index;
}

void Parser::Rollback()
{
	m_Index = m_Mark - 1;
	Next();
}

NodeList Parser::Parse(const TokenList& tokens)
{
	m_Tokens = tokens;
	m_Index = 0;
	Next();

	return ParseProgram();
}

NodeList Parser::ParseProgram()
{
	NodeList stmts;

	Node* n = nullptr;
	while ((n = ParseFnDef()) != nullptr)
	{
		stmts.push_back(n);
	}

	if (m_Current.Type != TokenType::Eof)
	{
		std::cout << "Parser error: Unexpected token!" << std::endl;
		for (;;);
	}

	return stmts;
}

Node* Parser::ParseFnDef()
{
	Mark();
	if (m_Current.Type == TokenType::Ident)
	{
		std::string name = m_Current.Value;
		Next();

		if (m_Current.Type == TokenType::Colon)
		{
			Next();

			if (m_Current.Type == TokenType::Left_Par)
			{
				Next();
				std::vector<Node*> params = ParseParameterList();

				if (m_Current.Type == TokenType::Right_Par)
				{
					Next();

					// Optional return type
					Node* ret = new TypeName("void");
					if (m_Current.Type == TokenType::Arrow)
					{
						Next();
						Node* type = ParseType();
						if (type)
						{
							delete ret;
							ret = type;
						}
						else
						{
							std::cout << "Expected type after ->" << std::endl;
							for (;;);
						}
					}

					if (m_Current.Type == TokenType::Left_Br)
					{
						Next();

						NodeList nodes = ParseStatementList();

						if (m_Current.Type == TokenType::Right_Br)
						{
							Next();
							return new FnDef(name, params, ret);
						}
						else
						{
							std::cout << "} expected" << std::endl;
							for (;;);
						}
					}
					else
					{
						std::cout << "{ expected" << std::endl;
						for (;;);
					}
				}
				else
				{
					std::cout << ") expected" << std::endl;
					for (;;);
				}
			}
		}
	}
	Rollback();

	return nullptr;
}

std::vector<Node*> Parser::ParseParameterList()
{
	std::vector<Node*> params;

	Node* param = ParseParameter();
	if (param)
	{
		params.push_back(param);
		while (m_Current.Type == TokenType::Comma)
		{
			Next();
			param = ParseParameter();
			if (param)
			{
				params.push_back(param);
			}
			else
			{
				std::cout << "parameter expected" << std::endl;
				for (;;);
			}
		}
	}

	return params;
}

Node* Parser::ParseParameter()
{
	Mark();
	if (m_Current.Type == TokenType::Ident)
	{
		std::string name = m_Current.Value;
		Next();
		if (m_Current.Type == TokenType::Colon)
		{
			Next();
			Node* type = ParseType();
			if (type)
			{
				return new ParamDef(name, type);
			}
		}
	}
	Rollback();
	return nullptr;
}

Node* Parser::ParseType()
{
	Mark();
	if (m_Current.Type == TokenType::Ident)
	{
		Node* type = new TypeName(m_Current.Value);
		Next();
		while (m_Current.Type == TokenType::Left_Sq)
		{
			Next();
			if (m_Current.Type == TokenType::Right_Sq)
			{
				Next();
				type = new ArrayType(type);
			}
			else
			{
				std::cout << "] expected" << std::endl;
				for (;;);
			}
		}

		return type;
	}
	Rollback();
	return nullptr;
}

std::vector<Node*> Parser::ParseStatementList()
{
	std::vector<Node*> stmts;

	return stmts;
}

Node* Parser::ParseStatement()
{

	return nullptr;
}
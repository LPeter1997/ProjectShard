#include <iostream>
#include <stack>
#include "Parser.h"

Parser::Parser()
{
	m_Precedence.insert(std::make_pair(TokenType::Plus		, OpDesc{ 2, false }));
	m_Precedence.insert(std::make_pair(TokenType::Minus		, OpDesc{ 2, false }));
	m_Precedence.insert(std::make_pair(TokenType::Star		, OpDesc{ 3, false }));
	m_Precedence.insert(std::make_pair(TokenType::Slash		, OpDesc{ 3, false }));
	m_Precedence.insert(std::make_pair(TokenType::Percent	, OpDesc{ 3, false }));
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

Node* Parser::ParseVarDecl()
{
	Mark();
	bool unif = false;
	if (m_Current.Type == TokenType::At)
	{
		unif = true;
		Next();
	}

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
				if (m_Current.Type == TokenType::Asgn)
				{
					Next();

					Node* val = ParseExpression();
					if (val)
					{
						if (unif)
						{
							return new UniformDef(name, type, val);
						}
						else
						{
							return new VarDef(name, type, val);
						}
					}
					else
					{
						std::cout << "Value expected" << std::endl;
						for (;;);
					}
				}
				else
				{
					if (unif)
					{
						return new UniformDecl(name, type);
					}
					else
					{
						return new VarDecl(name, type);
					}
				}
			}
			else
			{
				std::cout << "Type expected" << std::endl;
				for (;;);
			}
		}
	}

	Rollback();
	return nullptr;
}

static inline bool IsOp(TokenType tt)
{
	return tt == TokenType::Plus || tt == TokenType::Minus || tt == TokenType::Star || tt == TokenType::Slash || tt == TokenType::Percent;
}

Node* Parser::ParseExpression()
{
	std::stack<Operator*> operatorStack;
	std::vector<Node*> outputQueue;

	while (true)
	{
		Node* val = nullptr;
		if ((val = ParseValue()) != nullptr)
		{
			outputQueue.push_back(val);
		}
		else if (IsOp(m_Current.Type))
		{
			TokenType o1 = m_Current.Type;
			OpDesc o1d = m_Precedence.find(o1)->second;
			Next();

			Operator* o2 = operatorStack.top();
			while (o2 && o2->Type == NodeType::Operator)
			{
				OpDesc o2d = m_Precedence.find(o2->Op)->second;
				if ((!o1d.RightAssoc && o1d.Precedence <= o2d.Precedence) ||
					o1d.RightAssoc && o1d.Precedence < o2d.Precedence)
				{
					outputQueue.push_back(o2);
					operatorStack.pop();
				}
			}

			operatorStack.push(new Operator(o1));
		}
		else if (m_Current.Type == TokenType::Left_Par)
		{
			Next();
			operatorStack.push(new Operator(TokenType::Left_Par));
		}
		else if (m_Current.Type == TokenType::Right_Par)
		{
			Next();
			while (!operatorStack.empty() && operatorStack.top()->Op != TokenType::Left_Par)
			{
				Operator* op = operatorStack.top();
				outputQueue.push_back(op);
			}

			if (!operatorStack.empty())
			{
				operatorStack.pop();
			}
			else
			{
				std::cout << "() mismatch" << std::endl;
				for (;;);
			}
		}
		else
		{
			break;
		}
	}

	while (!operatorStack.empty())
	{
		if (operatorStack.top()->Op == TokenType::Left_Par || operatorStack.top()->Op == TokenType::Right_Par)
		{
			std::cout << "() mismatch" << std::endl;
			for (;;);
		}
		else
		{
			Operator* op = operatorStack.top();
			outputQueue.push_back(op);
		}
	}

	return nullptr;
}

Node* Parser::ParseValue()
{
	Mark();

	Rollback();
	return nullptr;
}
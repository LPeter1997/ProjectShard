#include <iostream>
#include <cctype>
#include "Lexer.h"

Lexer::Lexer()
{
}

Lexer::~Lexer()
{
}

TokenList Lexer::Tokenize(const std::string& src)
{
	return Tokenize(src.c_str());
}

TokenList Lexer::Tokenize(const char* src)
{
	TokenList tokens;

	while (*src)
	{
		switch (*src)
		{
			// Skip any whitespace
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			src++;
			break;

		case '(':
			src++;
			tokens.push_back(Token{ TokenType::Left_Par, "" });
			break;

		case ')':
			src++;
			tokens.push_back(Token{ TokenType::Right_Par, "" });
			break;

		case '{':
			src++;
			tokens.push_back(Token{ TokenType::Left_Br, "" });
			break;

		case '}':
			src++;
			tokens.push_back(Token{ TokenType::Right_Br, "" });
			break;

		case '+':
			src++;
			if (*src == '+')
			{
				src++;
				tokens.push_back(Token{ TokenType::Inc, "" });
			}
			else
			{
				tokens.push_back(Token{ TokenType::Plus, "" });
			}
			break;

		case '-':
			src++;
			if (*src == '-')
			{
				src++;
				tokens.push_back(Token{ TokenType::Dec, "" });
			}
			else if (*src == '>')
			{
				src++;
				tokens.push_back(Token{ TokenType::Arrow, "" });
			}
			else
			{
				tokens.push_back(Token{ TokenType::Minus, "" });
			}
			break;

		case '*':
			src++;
			tokens.push_back(Token{ TokenType::Star, "" });
			break;

		case '/':
			src++;
			tokens.push_back(Token{ TokenType::Slash, "" });
			break;

		case '%':
			src++;
			tokens.push_back(Token{ TokenType::Percent, "" });
			break;

		case '>':
			src++;
			if (*src == '=')
			{
				src++;
				tokens.push_back(Token{ TokenType::Goe, "" });
			}
			else
			{
				tokens.push_back(Token{ TokenType::Greater, "" });
			}
			break;

		case '<':
			src++;
			if (*src == '>')
			{
				src++;
				tokens.push_back(Token{ TokenType::Neq, "" });
			}
			else if (*src == '=')
			{
				src++;
				tokens.push_back(Token{ TokenType::Loe, "" });
			}
			else
			{
				tokens.push_back(Token{ TokenType::Less, "" });
			}
			break;

		case ':':
			src++;
			tokens.push_back(Token{ TokenType::Colon, "" });
			break;

		case '!':
			src++;
			tokens.push_back(Token{ TokenType::Ex, "" });
			break;

		case '?':
			src++;
			tokens.push_back(Token{ TokenType::Qu, "" });
			break;

		case ';':
			src++;
			tokens.push_back(Token{ TokenType::Semicol, "" });
			break;

		case '=':
			src++;
			if (*src == '=')
			{
				src++;
				tokens.push_back(Token{ TokenType::Eq, "" });
			}
			else if (*src == '>')
			{
				src++;
				tokens.push_back(Token{ TokenType::Darrow, "" });
			}
			else
			{
				tokens.push_back(Token{ TokenType::Asgn, "" });
			}
			break;

		case '$':
			src++;
			tokens.push_back(Token{ TokenType::Dollar, "" });
			break;

		case '.':
			src++;
			if (std::isdigit(*src))
			{
				std::string str = ".";
				while (std::isdigit(*src))
				{
					str += *src++;
				}

				tokens.push_back(Token{ TokenType::Real, str });
			}
			else
			{
				tokens.push_back(Token{ TokenType::Dot, "" });
			}
			break;

		case ',':
			src++;
			tokens.push_back(Token{ TokenType::Comma, "" });
			break;

		case '@':
			src++;
			tokens.push_back(Token{ TokenType::At, "" });
			break;

		case '[':
			src++;
			tokens.push_back(Token{ TokenType::Left_Sq, "" });
			break;

		case ']':
			src++;
			tokens.push_back(Token{ TokenType::Right_Sq, "" });
			break;

		default:
			if (std::isalpha(*src) || *src == '_')
			{
				std::string str = "";
				while (std::isalnum(*src) || *src == '_')
				{
					str += *src++;
				}
				if (str == "if")
					tokens.push_back(Token{ TokenType::Kw_If, "" });
				else if (str == "else")
					tokens.push_back(Token{ TokenType::Kw_Else, "" });
				else if (str == "elif")
					tokens.push_back(Token{ TokenType::Kw_Elif, "" });
				else
					tokens.push_back(Token{ TokenType::Ident, str });
			}
			else if (std::isdigit(*src))
			{
				std::string str = "";
				while (std::isdigit(*src))
				{
					str += *src++;
				}

				if (*src == '.')
				{
					src++;
					str += '.';
					while (std::isdigit(*src))
					{
						str += *src++;
					}
					tokens.push_back(Token{ TokenType::Real, str });
				}
				else
				{
					tokens.push_back(Token{ TokenType::Integer, str });
				}
			}
			else
			{
				std::cout << "Unrecognized token: " << *src << " (ASCII: " << +(*src) << ")!" << std::endl;
				for (;;);
			}
		}
	}

	tokens.push_back(Token{ TokenType::Eof, "" });
	tokens.push_back(Token{ TokenType::Epsilon, "" });
	return tokens;
}
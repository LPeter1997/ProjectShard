#pragma once

#include <vector>
#include "Types.h"
#include "Token.h"

typedef std::vector<Token> TokenList;

class Lexer
{
public:
	Lexer();
	~Lexer();

public:
	TokenList Tokenize(const char* src);
	TokenList Tokenize(const std::string& src);
};
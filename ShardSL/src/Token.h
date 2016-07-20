#pragma once

#include <string>

enum class TokenType
{
	// Single character tokens /////
	Left_Par, Right_Par,	// ( )
	Left_Br, Right_Br,		// { }
	Plus, Minus,			// + -
	Star, Slash, Percent,	// * / %
	Greater, Less,			// > <
	Colon, Ex, Qu,			// : ! ?
	Semicol, Asgn,			// ; =
	Dollar, Dot, Comma,		// $ . ,
	At,	Left_Sq, Right_Sq,	// @ [ ]

	// Double character tokens /////
	Eq, Neq,				// == <>
	Goe, Loe,				// >= <=
	Inc, Dec,				// ++ --
	Arrow, Darrow,			// -> =>

	// Keyword tokens ////////////////
	Kw_If, Kw_Else,			// if else
	Kw_Elif,				// elif

	// Other tokens //////////////////
	Ident,
	Integer, Real,
	Epsilon, Eof
};

struct Token
{
	TokenType	Type;
	std::string	Value;
};
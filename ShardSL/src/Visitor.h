#pragma once

#include "AST.h"

class Visitor
{
public:
	virtual void Visit(Node* node);

	virtual void Visit(FnDef* fn) {}
	virtual void Visit(ArrayType* fn) {}
	virtual void Visit(TypeName* fn) {}
	virtual void Visit(ParamDef* fn) {}
};
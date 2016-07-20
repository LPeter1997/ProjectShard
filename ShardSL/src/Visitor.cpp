#include "Visitor.h"

// FnDef, ArrayType, TypeName, ParamDef

void Visitor::Visit(Node* node)
{
	switch (node->Type)
	{
	case NodeType::FnDef:
		Visit((FnDef*)node);
		break;

	case NodeType::ArrayType:
		Visit((ArrayType*)node);
		break;

	case NodeType::TypeName:
		Visit((TypeName*)node);
		break;

	case NodeType::ParamDef:
		Visit((ParamDef*)node);
		break;
	}
}
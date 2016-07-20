#pragma once

#include <vector>

enum class NodeType
{
	FnDef, ArrayType, TypeName, ParamDef
};

struct Node
{
public:
	NodeType Type;

public:
	Node(NodeType t)
		: Type(t)
	{
	}
};

typedef std::vector<Node*> NodeList;

struct FnDef : public Node
{
public:
	std::string Name;
	std::vector<Node*> Arguments;
	Node* ReturnType;

public:
	FnDef(const std::string& nm, const std::vector<Node*>& args, Node* rt)
		: Node(NodeType::FnDef), Name(nm), Arguments(args), ReturnType(rt)
	{
	}
};

struct TypeName : public Node
{
public:
	std::string Name;

public:
	TypeName(const std::string& tn)
		: Node(NodeType::TypeName), Name(tn)
	{
	}
};

struct ArrayType : public Node
{
public:
	Node* ElementType;

public:
	ArrayType(Node* el)
		: Node(NodeType::ArrayType), ElementType(el)
	{
	}
};

struct ParamDef : public Node
{
public:
	std::string Name;
	Node* ParamType;

public:
	ParamDef(const std::string& nm, Node* pt)
		: Node(NodeType::ParamDef), Name(nm), ParamType(pt)
	{
	}
};
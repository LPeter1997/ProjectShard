#pragma once

#include <vector>

enum class NodeType
{
	FnDef, ArrayType, TypeName, ParamDef, VarDecl, VarDef, VarAss, UniformDecl, UniformDef, Operator
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

struct VarDecl : public Node
{
public:
	std::string Name;
	Node* VarType;

public:
	VarDecl(const std::string& nm, Node* tp)
		: Node(NodeType::VarDecl), Name(nm), VarType(tp)
	{
	}
};

struct VarDef : public Node
{
public:
	std::string Name;
	Node* VarType;
	Node* Value;

public:
	VarDef(const std::string& nm, Node* tp, Node* val)
		: Node(NodeType::VarDef), Name(nm), VarType(tp), Value(val)
	{
	}
};

struct VarAss : public Node
{
public:
	std::string Name;
	Node* Value;

public:
	VarAss(const std::string& nm, Node* val)
		: Node(NodeType::VarDef), Name(nm), Value(val)
	{
	}
};

struct UniformDecl : public Node
{
public:
	std::string Name;
	Node* VarType;

public:
	UniformDecl(const std::string& nm, Node* tp)
		: Node(NodeType::UniformDecl), Name(nm), VarType(tp)
	{
	}
};

struct UniformDef : public Node
{
public:
	std::string Name;
	Node* VarType;
	Node* Value;

public:
	UniformDef(const std::string& nm, Node* tp, Node* val)
		: Node(NodeType::UniformDef), Name(nm), VarType(tp), Value(val)
	{
	}
};

struct Operator : public Node
{
public:
	TokenType Op;

public:
	Operator(TokenType op)
		: Node(NodeType::Operator), Op(op)
	{
	}
};
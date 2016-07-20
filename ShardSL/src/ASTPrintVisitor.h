#pragma once

#include <string>
#include <iostream>
#include "Visitor.h"

class ASTPrintVisitor : public Visitor
{
private:
	std::string m_Indent;

public:
	void Visit(Node* n) override { Visitor::Visit(n); }

	void Visit(FnDef* fn) override
	{
		std::cout << m_Indent << "Function: " << fn->Name << std::endl;
		std::cout << m_Indent << "Args:" << std::endl;
		std::cout << m_Indent << "[" << std::endl;
		m_Indent += " ";
		for (Node* n : fn->Arguments)
		{
			Visitor::Visit(n);
			std::cout << m_Indent << "," << std::endl;
		}
		m_Indent = m_Indent.substr(1);
		std::cout << m_Indent << "]" << std::endl;
		std::cout << "ReturnType: ";
		Visitor::Visit(fn->ReturnType);
		std::cout << std::endl;
	}

	void Visit(ArrayType* fn) override
	{
		std::cout << m_Indent << "Array" << std::endl;
		std::cout << m_Indent << "[" << std::endl;
		m_Indent += " ";
		Visitor::Visit(fn->ElementType);
		m_Indent = m_Indent.substr(1);
		std::cout << std::endl;
		std::cout << m_Indent << "]" << std::endl;
	}
	
	void Visit(TypeName* fn) override
	{
		std::cout << m_Indent << "TypeName: " << fn->Name;
	}

	void Visit(ParamDef* fn) override
	{
		std::cout << m_Indent << "Param" << std::endl;
		std::cout << m_Indent << "[" << std::endl;
		m_Indent += " ";
		std::cout << m_Indent << "Name: " << fn->Name << std::endl;
		Visitor::Visit(fn->ParamType);
		m_Indent = m_Indent.substr(1);
		std::cout << std::endl << m_Indent << "]" << std::endl;
	}
};
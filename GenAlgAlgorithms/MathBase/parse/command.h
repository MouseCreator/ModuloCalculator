

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <stdint.h>

#include "errloc.h"

namespace MathBase {

/**
 * AST node.
 */
class ASTNode {
public:
	virtual std::string str() {
		return "";
	}
	virtual merr::LocationStruct loc() {
		return merr::LocationStruct();
	}
	virtual ~ASTNode() {
		
	}
};

class AST {
private:
	ASTNode* root = nullptr;
public:
	ASTNode* getRoot() {
		return root;
	}
    AST(ASTNode* root) {
        this->root = root;
    }
    AST() {
        this->root = nullptr;
    }
    ~AST() {
		delete root;
    }
	std::string str() {
		if (root) {
			return root->str();
		} else {
			return "";
		}
	}
};
class OperationNode : public ASTNode {
public:
	ASTNode* left = nullptr;
	ASTNode* right = nullptr;
	std::string operation;
	merr::LocationStruct m_loc;
	OperationNode(ASTNode* left, std::string op, ASTNode* right, merr::LocationStruct loc) {
		this->left = left;
		this->right = right;
		this->operation = op;
		this->m_loc = loc;
	}
	~OperationNode() {
		delete left;
		delete right;
	}
	std::string str() {
		return "(" + left->str() + operation + right->str() + ")";
	}
	merr::LocationStruct loc() {
		return m_loc;
	}
};

class ComparisonNode : public ASTNode {
public:
	ASTNode* left = nullptr;
	ASTNode* right = nullptr;
	std::string operation;
	merr::LocationStruct m_loc;
	ComparisonNode(ASTNode* left, std::string operation, ASTNode* right, merr::LocationStruct loc) {
		this->left = left;
		this->right = right;
		this->operation = operation;
		this->m_loc = loc;
	}
	~ComparisonNode() {
		delete left;
		delete right;
	}
	std::string str() {
		return  left->str() + operation + right->str();
	}
	merr::LocationStruct loc() {
		return m_loc;
	}
};

class UnaryNode : public ASTNode {
public:
	ASTNode* target;
	std::string operation;
	merr::LocationStruct m_loc;
	UnaryNode(std::string operation, ASTNode* target, merr::LocationStruct loc) {
		this->target = target;
		this->operation = operation;
		this->m_loc = loc;
	}
	std::string str() {
		return  operation + "(" + target->str() + ")";
	}
	~UnaryNode() {
		delete target;
	}
	merr::LocationStruct loc() {
		return m_loc;
	}
};

class ValueNode : public ASTNode {
};
class NumberNode : public ValueNode {
public:
	std::string digits;
	merr::LocationStruct m_loc;
	NumberNode(std::string digits, merr::LocationStruct loc) {
		this->digits = digits;
		this->m_loc = loc;
	}
	std::string str() {
		return digits;
	}
	merr::LocationStruct loc() {
		return m_loc;
	}
};
class VariableNode : public ValueNode {
public:
	std::string var_name;
	merr::LocationStruct m_loc;
	VariableNode(std::string var_name, merr::LocationStruct loc) {
		this->var_name = var_name;
		this->m_loc = loc;
	}
	std::string str() {
		return var_name;
	}
	merr::LocationStruct loc() {
		return m_loc;
	}
};
class FunctionNode : public ASTNode {
public:
	std::string functionName;
	std::vector<ASTNode*> arguments;
	merr::LocationStruct m_loc;
	std::size_t num_argumnets() {
		return arguments.size();
	}
	FunctionNode(std::string name, std::vector<ASTNode*> arguments, merr::LocationStruct loc) {
		this->functionName = name;
		this->arguments = arguments;
		this->m_loc = loc;
	}
	bool isNamed(std::string expected_name) {
		return expected_name == functionName;
	}
	std::string str() {
		std::string result = functionName + "(";
		std::size_t size = arguments.size();
		if (size == 0) {
			return result + ")";
		}
		result += arguments[0]->str();
		for (std::size_t i = 1; i < size; i++) {
			result += ", ";
			result += arguments[i]->str();
		}
		result += ")";
		return result;
	}
	~FunctionNode() {
		for (ASTNode* node : arguments) {
			delete node;
		}
		arguments.clear();
	}
	merr::LocationStruct loc() {
		return m_loc;
	}
};
}

#endif // COMMAND_H

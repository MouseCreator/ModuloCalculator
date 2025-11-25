#include "command.h"
#include "../AST_Generic_Visitor.h"
namespace MathBase {

	OperationNode::OperationNode(ASTNode* left, std::string op, ASTNode* right, merr::LocationStruct location) {
		this->left = left;
		this->right = right;
		this->operation = op;
		this->m_loc = location;
	}
	OperationNode::~OperationNode() {
		if (left) {
			delete left;
		}
		if (right) {
			delete right;
		}
	}
	std::string OperationNode::str() {
		return "(" + left->str() + operation + right->str() + ")";
	}
	merr::LocationStruct& OperationNode::loc() {
		return m_loc;
	}

	void OperationNode::acceptVisitor(ASTVisitor* visitor) {
		visitor->visitOperation(*this);
	}

	ComparisonNode::ComparisonNode(ASTNode* left, std::string operation, ASTNode* right, merr::LocationStruct location) {
		this->left = left;
		this->right = right;
		this->operation = operation;
		this->m_loc = location;
	}
	ComparisonNode::~ComparisonNode() {
		if (left)
			delete left;
		if (right)
			delete right;
	}
	merr::LocationStruct& ComparisonNode::loc() {
		return m_loc;
	}
	void ComparisonNode::acceptVisitor(ASTVisitor* visitor) {
		visitor->raiseError("Comparison nodes are not supported");
	}

	std::string ComparisonNode::str() {
		return  left->str() + operation + right->str();
	}

	UnaryNode::UnaryNode(std::string operation, ASTNode* target, merr::LocationStruct location) {
		this->target = target;
		this->operation = operation;
		this->m_loc = location;
	}
	merr::LocationStruct& UnaryNode::loc() {
		return m_loc;
	}
	std::string UnaryNode::str() {
		return  operation + "(" + target->str() + ")";
	}
	UnaryNode::~UnaryNode() {
		delete target;
	}
	void UnaryNode::acceptVisitor(ASTVisitor* visitor) {
		visitor->visitUnary(*this);
	}

	NumberNode::NumberNode(std::string digits, merr::LocationStruct location) {
		this->digits = digits;
		this->m_loc = location;
	}
	std::string NumberNode::str() {
		return digits;
	}
	void NumberNode::acceptVisitor(ASTVisitor* visitor) {
		visitor->visitNumber(*this);
	}
	merr::LocationStruct& NumberNode::loc() {
		return m_loc;
	}
	std::size_t FunctionNode::num_argumnets() {
		return arguments.size();
	}
	FunctionNode::FunctionNode(std::string name, std::vector<ASTNode*> arguments, merr::LocationStruct location) {
		this->functionName = name;
		this->arguments = arguments;
		this->m_loc = location;
	}
	void FunctionNode::acceptVisitor(ASTVisitor* visitor) {
		visitor->visitFunction(*this);
	}
	bool FunctionNode::isNamed(std::string expected_name) {
		return expected_name == functionName;
	}
	merr::LocationStruct& FunctionNode::loc() {
		return m_loc;
	}
	std::string FunctionNode::str() {
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
	FunctionNode::~FunctionNode() {
		for (ASTNode* node : arguments) {
			delete node;
		}
		arguments.clear();
	}
}
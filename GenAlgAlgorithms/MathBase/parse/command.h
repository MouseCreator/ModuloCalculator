

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <stdint.h>
#include "../AST_Core.h"
namespace MathBase {

	class OperationNode : public ASTNode {
	private:
		merr::LocationStruct m_loc;
	public:
		ASTNode* left = nullptr;
		ASTNode* right = nullptr;
		std::string operation;
		OperationNode(ASTNode* left, std::string op, ASTNode* right, merr::LocationStruct location);
		~OperationNode();
		std::string str() override;
		merr::LocationStruct& loc() override;
		void acceptVisitor(ASTVisitor* visitor) override;
	};

	class ComparisonNode : public ASTNode {
	private:
		merr::LocationStruct m_loc;
	public:
		ASTNode* left = nullptr;
		ASTNode* right = nullptr;
		std::string operation;
		ComparisonNode(ASTNode* left, std::string operation, ASTNode* right, merr::LocationStruct location);
		~ComparisonNode();
		std::string str() override;
		merr::LocationStruct& loc() override;
		void acceptVisitor(ASTVisitor* visitor) override;
	};

	class UnaryNode : public ASTNode {
	private:
		merr::LocationStruct m_loc;
	public:
		ASTNode* target;
		std::string operation;
		UnaryNode(std::string operation, ASTNode* target, merr::LocationStruct location);
		~UnaryNode();
		std::string str() override;
		merr::LocationStruct& loc() override;
		void acceptVisitor(ASTVisitor* visitor) override;
	};

	class ValueNode : public ASTNode {
	};
	class NumberNode : public ValueNode {
	private:
		merr::LocationStruct m_loc;
	public:
		std::string digits;
		NumberNode(std::string digits, merr::LocationStruct location);
		std::string str() override;
		merr::LocationStruct& loc() override;
		void acceptVisitor(ASTVisitor* visitor) override;
	};
	class FunctionNode : public ASTNode {
	private:
		merr::LocationStruct m_loc;
	public:
		std::string functionName;
		std::vector<ASTNode*> arguments;
		merr::LocationStruct& loc() override;

		std::size_t num_argumnets();
		FunctionNode(std::string name, std::vector<ASTNode*> arguments, merr::LocationStruct location);
		bool isNamed(std::string expected_name);
		~FunctionNode();
		std::string str() override;
		void acceptVisitor(ASTVisitor* visitor) override;
	};
}

#endif // COMMAND_H

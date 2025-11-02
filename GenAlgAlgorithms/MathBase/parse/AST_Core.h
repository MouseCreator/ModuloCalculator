#pragma once
#include <iostream>
#include "../merr/errloc.h"

namespace MathBase {
	class ASTVisitor;
	class ASTNode {
	public:
		virtual std::string str() = 0;
		virtual ~ASTNode() {}
		virtual void acceptVisitor(ASTVisitor* visitor) = 0;
		virtual merr::LocationStruct& loc() = 0;
	};

	class AST {
	private:
		ASTNode* root;
	public:
		ASTNode* getRoot();
		AST(ASTNode* root);
		AST();
		~AST();
		std::string str();
		
		void acceptVisitor(ASTVisitor* visitor);
	};
}
#include "AST_Core.h"


namespace MathBase {

	ASTNode* AST::getRoot() {
		return root;
	}
	AST::AST(ASTNode* root) {
		this->root = root;
	}
	AST::AST() {
		this->root = nullptr;
	}
	AST::~AST() {
		delete root;
	}
	std::string AST::str() {
		if (root) {
			return root->str();
		}
		else {
			return "";
		}
	}
	void AST::acceptVisitor(ASTVisitor* visitor) {
		this->root->acceptVisitor(visitor);
	}
}
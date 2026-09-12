#include "AST.h"
#include <iostream>

void LiteralNode::print() const {
    std::cout << value;
}

void LiteralNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}


void StarNode::print() const {
    std::cout << "(";
    if (child) {
        child->print();
    }
    std::cout << "*)";
}

void StarNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

void ConcatNode::print() const {
    std::cout << "(";
    if (left) { left->print(); }
    if (right) { right->print(); }
    std::cout << ")";
}

void ConcatNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}

void UnionNode::print() const {
    std::cout << "(";
    if (left) { left->print(); }
    std::cout << "|";
    if (right) { right->print(); }
    std::cout << ")";
}

void UnionNode::accept(ASTVisitor &visitor) {
    visitor.visit(*this);
}
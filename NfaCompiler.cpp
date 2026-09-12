//
// Created by Noam Apelfeld on 12/09/2026.
//

#include "NFACompiler.h"

void NFACompiler::visit(LiteralNode &node) {
    last_pair = builder.create_literal(node.get_value());
}

void NFACompiler::visit(StarNode &node) {
    node.getChild()->accept(*this);
    last_pair = builder.create_star(last_pair);
}

void NFACompiler::visit(ConcatNode &node) {
    node.getLeft()->accept(*this);
    State_Pair left_pair = last_pair;
    node.getRight()->accept(*this);
    last_pair = builder.create_concat(left_pair, last_pair);
}

void NFACompiler::visit(UnionNode &node) {
    node.getLeft()->accept(*this);
    State_Pair left_pair = last_pair;
    node.getRight()->accept(*this);
    last_pair = builder.create_union(left_pair, last_pair);
}

NFA NFACompiler::compile(RegexNode &root) {
    root.accept(*this);
    return builder.build(last_pair);
}

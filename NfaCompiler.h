//
// Created by Noam Apelfeld on 12/09/2026.
//

#ifndef AUTOMAT_NFACOMPILER_H
#define AUTOMAT_NFACOMPILER_H

#include "AST.h"
#include "Nfa.h"

class NFACompiler : public ASTVisitor {
private:
    NFABuilder builder;
    State_Pair last_pair;

public:
    void visit(LiteralNode &node) override;
    void visit(StarNode &node) override;
    void visit(ConcatNode &node) override;
    void visit(UnionNode &node) override;

    NFA compile(RegexNode &root);
};

#endif // AUTOMAT_NFACOMPILER_H
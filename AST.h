#ifndef AUTOMAT_AST_H
#define AUTOMAT_AST_H

#include <memory>
#include <utility>

class LiteralNode;

class StarNode;

class ConcatNode;

class UnionNode;

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;
    virtual void visit(LiteralNode &node) = 0;
    virtual void visit(StarNode &node) = 0;
    virtual void visit(UnionNode &node) = 0;
    virtual void visit(ConcatNode &node) = 0;
};

class RegexNode {
public:
    virtual ~RegexNode() = default;
    virtual void print() const = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};

class LiteralNode : public RegexNode {
private:
    char value;

public:
    explicit LiteralNode(char val) : value(val) {}

    char get_value() const { return value; }

    void print() const override;
    void accept(ASTVisitor &visitor) override;
};

class StarNode : public RegexNode {
private:
    std::unique_ptr<RegexNode> child;

public:
    explicit StarNode(std::unique_ptr<RegexNode> c) : child(std::move(c)) {}

    RegexNode *getChild() { return child.get(); }

    const RegexNode *getChild() const { return child.get(); }

    void print() const override;
    void accept(ASTVisitor &visitor) override;
};

class ConcatNode : public RegexNode {
private:
    std::unique_ptr<RegexNode> left;
    std::unique_ptr<RegexNode> right;

public:
    ConcatNode(std::unique_ptr<RegexNode> left, std::unique_ptr<RegexNode> right)
            : left(std::move(left)), right(std::move(right)) {}

    RegexNode *getLeft() { return left.get(); }

    const RegexNode *getLeft() const { return left.get(); }

    RegexNode *getRight() { return right.get(); }

    const RegexNode *getRight() const { return right.get(); }

    void print() const override;
    void accept(ASTVisitor &visitor) override;
};

class UnionNode : public RegexNode {
private:
    std::unique_ptr<RegexNode> left;
    std::unique_ptr<RegexNode> right;

public:
    UnionNode(std::unique_ptr<RegexNode> left, std::unique_ptr<RegexNode> right)
            : left(std::move(left)), right(std::move(right)) {}

    RegexNode *getLeft() { return left.get(); }

    const RegexNode *getLeft() const { return left.get(); }

    RegexNode *getRight() { return right.get(); }

    const RegexNode *getRight() const { return right.get(); }

    void print() const override;
    void accept(ASTVisitor &visitor) override;
};

#endif // AUTOMAT_AST_H
//
// Created by Noam Apelfeld on 12/09/2026.
//

#include "Parser.h"
#include <stdexcept>
#include <utility>

Parser::Parser(std::string regex) : src(std::move(regex)), idx(0) {}

std::unique_ptr<RegexNode> Parser::parse() {
    auto root = parse_expr();
    if (peek() != '\0') {
        throw std::runtime_error("Unexpected character in regex");
    }
    return root;
}

std::unique_ptr<RegexNode> Parser::parse_expr() {
    auto left = parse_concat();
    while (match('|')) {
        auto right = parse_concat();
        left = std::make_unique<UnionNode>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<RegexNode> Parser::parse_concat() {
    auto left = parse_star();
    while (can_start()) {
        auto right = parse_star();
        left = std::make_unique<ConcatNode>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<RegexNode> Parser::parse_star() {
    auto node = parse_base();
    while (match('*')) {
        node = std::make_unique<StarNode>(std::move(node));
    }
    return node;
}

std::unique_ptr<RegexNode> Parser::parse_base() {
    if (match('(')) {
        auto node = parse_expr();
        if (!match(')')) {
            throw std::runtime_error("invalid regex: missing closing parenthesis");
        }
        return node;
    }

    if (can_start()) {
        return std::make_unique<LiteralNode>(advance());
    }

    throw std::runtime_error("invalid regex: unexpected token in expression");
}

bool Parser::can_start() const {
    char c = peek();
    return c != ')' && c != '*' && c != '|' && c != '\0';
}

char Parser::peek() const {
    if (idx >= src.size()) {
        return '\0';
    }
    return src[idx];
}

char Parser::advance() {
    if (idx >= src.size()) {
        return '\0';
    }
    return src[idx++];
}

bool Parser::match(char other) {
    if (peek() == other) {
        advance();
        return true;
    }
    return false;
}

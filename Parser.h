//
// Created by Noam Apelfeld on 12/09/2026.
//

#ifndef AUTOMAT_PARSER_H
#define AUTOMAT_PARSER_H

#include <memory>
#include <string>
#include "AST.h"

class Parser {
private:
    std::string src;
    size_t idx = 0;

    std::unique_ptr<RegexNode> parse_expr();
    std::unique_ptr<RegexNode> parse_concat();
    std::unique_ptr<RegexNode> parse_star();
    std::unique_ptr<RegexNode> parse_base();

    bool can_start() const;
    char peek() const;
    char advance();
    bool match(char other);

public:
    explicit Parser(std::string regex);

    std::unique_ptr<RegexNode> parse();
};

#endif // AUTOMAT_PARSER_H
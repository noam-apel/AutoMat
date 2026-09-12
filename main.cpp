#include <iostream>
#include "Parser.h"
#include "NFACompiler.h"

void test(const std::string &pattern, const std::string &input, bool expected) {
    Parser parser(pattern);
    auto ast = parser.parse();

    NFACompiler compiler;
    NFA nfa = compiler.compile(*ast);

    bool result = nfa.match(input);
    std::cout << "Pattern: /" << pattern << "/ on \"" << input << "\" -> "
              << (result ? "MATCH" : "REJECT")
              << " (" << (result == expected ? "PASS" : "FAIL") << ")\n";
}

int main() {
    Parser parser("(a|b)");
    auto ast = parser.parse();

    NFACompiler compiler;
    NFA nfa = compiler.compile(*ast);
    std::cout << nfa.match("a");
}
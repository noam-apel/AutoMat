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
    test("(a|b)*c", "c", true);
    test("(a|b)*c", "ac", true);
    test("(a|b)*c", "abbabac", true);
    test("(a|b)*c", "abbaba", false);
    test("(a|b)*c", "", false);
    test("a*", "", true);
    test("a*", "aaaa", true);
    test("a*", "b", false);
    return 0;
}
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "dfa.h"

int main() {
    std::string input;
    std::cin >> input;
    Parser p(input);
    AST a = p.parse();
    DFA d = AST2DFA(a);
    crawl(d);
    return 0;
}

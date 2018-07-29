#include "token.h"
#include "lexer.h"
#include "parser.h"

int main() {
    std::string input;
    std::cin >> input;
    Parser p(input);
    std::cout << p.parse() << std::endl;
    return 0;
}

#include "token.h"
#include "lexer.h"
#include "parser.h"

int main() {
    std::string input;
    std::cin >> input;
    Lexer lex(input);
    while(true){
        Token t = lex.nextToken();
        std::cout << t << " ";
        if(t.type == END) {
            break;
        }
    }
    std::cout << std::endl;
    Parser p(input);
    std::cout << p.parse() << std::endl;
    return 0;
}

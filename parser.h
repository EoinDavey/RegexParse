#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "token.h"
#include "ast.h"
#include <memory>

class Parser {
    private:
        Lexer l;
        Token tok;
        std::unique_ptr<AST::Node> re();
        std::unique_ptr<AST::Node> o();
        std::unique_ptr<AST::Node> s();
        std::unique_ptr<AST::Node> lit();
        bool accept(Type);
        bool expect(Type);
        bool peek(Type);
    public:
        Parser(std::string);
        AST parse();
};

#endif

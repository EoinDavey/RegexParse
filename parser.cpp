/*
 * RE ::= O | O . RE
 * O  ::= S | S `|` O
 * S  ::= LIT | LIT *
 * LIT ::= [a-z] | ( RE )
 */

#include "parser.h"
#include <iostream>
#define EXPCT(s) if(expect(s)) return nodeptr{};
#define CHECK(s) if(!s) return nodeptr{};

Parser::Parser(std::string input) : l(Lexer(input)) {}

typedef std::unique_ptr<AST::Node> nodeptr;

AST Parser::parse() {
    tok = l.nextToken();
    auto d = re();
    if(!d || tok.type != END) {
        std::cout << "could not parse" << std::endl;
        return AST{};
    }
    return AST(std::move(d));
}

bool Parser::accept(Type t) {
    if(tok.type == t) {
        tok = l.nextToken();
        return true;
    }
    return false;
}

bool Parser::peek(Type t) {
    return tok.type == t;
}

bool Parser::expect(Type t) {
    if(tok.type == t) {
        tok = l.nextToken();
        return false;
    }
    std::cout << "unexpected " << tok.literal << std::endl;
    return true;
}

nodeptr Parser::re() {
    auto l = o();
    CHECK(l);
    if(peek(LIT) || peek(LPAREN)) {
        auto n = std::make_unique<AST::Node>();
        n->op = CATOP;
        n->l = std::move(l);
        auto r = re();
        CHECK(r);
        n->r = std::move(r);
        return n;
    }
    return l;
}

nodeptr Parser::o() {
    auto l = s();
    CHECK(l);
    if(accept(OR)){
        auto n = std::make_unique<AST::Node>();
        n->op = OROP;
        n->l = std::move(l);
        auto r = o();
        CHECK(r);
        n->r = std::move(r);
        return n;
    }
    return l;
}

nodeptr Parser::s() {
    auto l = lit();
    CHECK(l);
    if(accept(STAR)){
        auto n = std::make_unique<AST::Node>();
        n->op = STAROP;
        n->l = std::move(l);
        return n;
    }
    return l;
}

nodeptr Parser::lit() {
    nodeptr n = std::make_unique<AST::Node>();
    if(accept(LPAREN)) {
        n = re();
        EXPCT(RPAREN);
        return n;
    } else if(peek(LIT)) {
        n->op = LITOP;
        n->v = tok.literal;
        EXPCT(LIT);
        return n;
    }
    return nodeptr{};
}

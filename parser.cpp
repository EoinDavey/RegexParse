/*
 * RE ::= O | O . RE
 * O  ::= S | S `|` O
 * S  ::= LIT | LIT * | LIT + | LIT ?
 * LIT ::= [a-z] | ( RE )
 */

#include "parser.h"

#include <iostream>

#define XPCT(s) if(expect(s)) return nodeptr{};
#define CHECK(s) if(!s) return nodeptr{};

Parser::Parser(std::string input) : l(Lexer(input)) {}

typedef std::unique_ptr<AST::Node> nodeptr;

AST Parser::parse() {
    tok = l.nextToken();
    auto d = re();
    if(!d || tok.type != END) {
        std::cerr << "could not parse" << std::endl;
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
    std::cerr << "unexpected " << tok.literal << std::endl;
    return true;
}

nodeptr Parser::re() {
    nodeptr l = o();
    CHECK(l);
    if(peek(LIT) || peek(LPAREN)) {
        nodeptr n = std::make_unique<AST::Node>();
        n->op = CATOP;
        n->l = std::move(l);
        nodeptr r = re();
        CHECK(r);
        n->r = std::move(r);
        return n;
    }
    return l;
}

nodeptr Parser::o() {
    nodeptr l = s();
    CHECK(l);
    if(accept(OR)){
        nodeptr n = std::make_unique<AST::Node>();
        n->op = OROP;
        n->l = std::move(l);
        nodeptr r = o();
        CHECK(r);
        n->r = std::move(r);
        return n;
    }
    return l;
}

nodeptr Parser::s() {
    nodeptr l = lit();
    CHECK(l);
    if(accept(STAR)){
        nodeptr n = std::make_unique<AST::Node>();
        n->op = STAROP;
        n->l = std::move(l);
        return n;
    }
    if(accept(PLUS)){
        nodeptr n = std::make_unique<AST::Node>();
        n->op = PLUSOP;
        n->l = std::move(l);
        return n;
    }
    if(accept(OPT)){
        nodeptr n = std::make_unique<AST::Node>();
        n->op = OPTOP;
        n->l = std::move(l);
        return n;
    }
    return l;
}

nodeptr Parser::lit() {
    nodeptr n = std::make_unique<AST::Node>();
    if(accept(LPAREN)) {
        n = re();
        XPCT(RPAREN);
        return n;
    } else if(peek(LIT)) {
        n->op = LITOP;
        n->v = tok.literal;
        XPCT(LIT);
        return n;
    }
    return nodeptr{};
}

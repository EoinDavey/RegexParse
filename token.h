/*
 * RE ::= O | RE . O
 * O ::= S | O `|` S
 * S ::= B | B *
 * B ::= L | ( RE )
 * L ::= [a - z] | e
 */
#ifndef TOKEN_H
#define TOKEN_H
#include<string>
#include <iostream>

enum Type { LIT=0, OR, STAR, END, LPAREN, RPAREN};
extern const char* typeStrs[6];

class Token {
    public:
        Token(Type, std::string);
        Token();
        Type type;
        std::string literal;
    friend std::ostream& operator<<(std::ostream&,const Token&);
};
#endif

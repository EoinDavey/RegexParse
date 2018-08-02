/*
 * RE ::= O | RE . O
 * O ::= S | O `|` S
 * S ::= B | B *
 * B ::= L | ( RE )
 * L ::= [a - z] | e
 */
#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

enum Type { LIT=0, OR, STAR, END, LPAREN, RPAREN};
extern const char* typeStrs[6];

class Token {
    public:
        Token(Type, char);
        Token();
        Type type;
        char literal;
    friend std::ostream& operator<<(std::ostream&,const Token&);
};
#endif

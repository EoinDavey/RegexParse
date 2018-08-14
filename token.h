#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

enum Type { LIT=0, OR, STAR, PLUS, OPT, END, LPAREN, RPAREN};
extern const char* typeStrs[8];

class Token {
    public:
        Token(Type, char);
        Token();
        Type type;
        char literal;
    friend std::ostream& operator<<(std::ostream&,const Token&);
};
#endif

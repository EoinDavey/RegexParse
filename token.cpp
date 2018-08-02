#include "token.h"

const char* typeStrs[] = {"LIT","OR","STAR","END","LPAREN","RPAREN"};

Token::Token(Type t, char c) : type(t), literal(c) {}
Token::Token(){}

std::ostream& operator<< (std::ostream &out, const Token& t) {
    out << "(" << typeStrs[t.type] << "," << t.literal << ")";
    return out;
}

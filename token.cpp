#include "token.h"


const char* typeStrs[] = {"LIT","OR","STAR","END","LPAREN","RPAREN"};
Token::Token(Type t, std::string s) : type(t), literal(s) {}
Token::Token(){}
std::ostream& operator<< (std::ostream &out, const Token& t) {
    out << "(" << typeStrs[t.type] << "," << t.literal << ")";
    return out;
}

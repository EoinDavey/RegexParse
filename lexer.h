#ifndef LEXER_H
#define LEXER_H
#include <string>
#include "token.h"

class Lexer {
    public:
        Lexer(std::string);
        Token nextToken(void);
        
    private:
        const std::string input;
        int head_pos;
        int read_pos;
        char ch;

        void skipWhitespace(void);
        void readChar(void);
};
#endif

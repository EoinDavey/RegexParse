#include "lexer.h"
#include <stdio.h>

Lexer::Lexer(std::string s) : input(s){
    ch = s[0];
    read_pos = 1;
    head_pos = 0;
}

Token Lexer::nextToken() {
    skipWhitespace();
    Token t;
    switch(ch) {
        case '|':
            t = Token(OR, '|');
            break;
        case '\0':
            t = Token(END, '%');
            break;
        case '*':
            t = Token(STAR, '*');
            break;
        case '+':
            t = Token(PLUS, '+');
            break;
        case '(':
            t = Token(LPAREN, '(');
            break;
        case ')':
            t = Token(RPAREN, ')');
            break;
        case '?':
            t = Token(OPT, '?');
            break;
        case '\\':
            readChar();
            if(ch == '|' || ch == '*' || ch == '+' || ch == '?' ||
                    ch == '(' || ch == ')' || ch == '\\') {
                t = Token(LIT, ch);
            } else {
                t = Token(END, '%');
                printf("Invalid escape code \\%c", ch);
            }
            break;
       default:
            t = Token(LIT, ch);
    }
    readChar();
    return t;
}

void Lexer::readChar() {
    if(read_pos >= input.length()) {
        ch = '\0';
    } else {
        ch = input[read_pos];
        head_pos = read_pos;
        ++read_pos;
    }
}

void Lexer::skipWhitespace() {
    while(ch=='\t' || ch=='\n' || ch=='r') {
        readChar();
    }
}

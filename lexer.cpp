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
            t = std::move(Token(OR, '|'));
            break;
        case '\0':
            t = std::move(Token(END, '%'));
            break;
        case '*':
            t = std::move(Token(STAR, '*'));
            break;
        case '(':
            t = std::move(Token(LPAREN, '('));
            break;
        case ')':
            t = std::move(Token(RPAREN, ')'));
            break;
       default:
            t = std::move(Token(LIT, ch));
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

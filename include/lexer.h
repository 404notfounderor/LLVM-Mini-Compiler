#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
    TOKEN_EOF,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_EQUAL,
    TOKEN_SEMICOLON,
    TOKEN_IF,
    TOKEN_WHILE,
    TOKEN_LPAREN,
    TOKEN_RPAREN
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    int pos;

    char currentChar();
    void advance();
};

#endif
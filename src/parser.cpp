#include "parser.h"
#include <cstdlib>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

Token Parser::currentToken() {
    return tokens[pos];
}

void Parser::advance() {
    pos++;
}

std::unique_ptr<Expr> Parser::parse() {

    // IF
    if (currentToken().type == TOKEN_IF) {
        advance(); // if
        advance(); // (
        auto cond = parseExpression();
        advance(); // )

        auto body = parse();
        return std::make_unique<IfExpr>(std::move(cond), std::move(body));
    }

    // WHILE
    if (currentToken().type == TOKEN_WHILE) {
        advance();
        advance();
        auto cond = parseExpression();
        advance();

        auto body = parse();
        return std::make_unique<WhileExpr>(std::move(cond), std::move(body));
    }

    // Assignment
    std::string name = currentToken().value;
    advance();
    advance();

    auto expr = parseExpression();
    return std::make_unique<AssignmentExpr>(name, std::move(expr));
}

std::unique_ptr<Expr> Parser::parseExpression() {
    auto left = std::make_unique<NumberExpr>(std::stoi(currentToken().value));
    advance();

    while (currentToken().type == TOKEN_PLUS) {
        advance();
        auto right = std::make_unique<NumberExpr>(std::stoi(currentToken().value));
        advance();

        left = std::make_unique<BinaryExpr>('+', std::move(left), std::move(right));
    }

    return left;
}
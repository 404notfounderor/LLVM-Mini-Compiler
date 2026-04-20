#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include "llvm/IR/Value.h"

class CodeGenContext;

class Expr {
public:
    virtual ~Expr() {}
    virtual llvm::Value* codegen(CodeGenContext& context) = 0;
};

class NumberExpr : public Expr {
public:
    int value;
    NumberExpr(int val);
    llvm::Value* codegen(CodeGenContext& context) override;
};

class VariableExpr : public Expr {
public:
    std::string name;
    VariableExpr(const std::string& name);
    llvm::Value* codegen(CodeGenContext& context) override;
};

class BinaryExpr : public Expr {
public:
    char op;
    std::unique_ptr<Expr> left, right;

    BinaryExpr(char op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right);
    llvm::Value* codegen(CodeGenContext& context) override;
};

class AssignmentExpr : public Expr {
public:
    std::string name;
    std::unique_ptr<Expr> value;

    AssignmentExpr(const std::string& name, std::unique_ptr<Expr> value);
    llvm::Value* codegen(CodeGenContext& context) override;
};

class IfExpr : public Expr {
public:
    std::unique_ptr<Expr> condition, thenBranch;

    IfExpr(std::unique_ptr<Expr> cond, std::unique_ptr<Expr> thenB);
    llvm::Value* codegen(CodeGenContext& context) override;
};

class WhileExpr : public Expr {
public:
    std::unique_ptr<Expr> condition, body;

    WhileExpr(std::unique_ptr<Expr> cond, std::unique_ptr<Expr> body);
    llvm::Value* codegen(CodeGenContext& context) override;
};

#endif
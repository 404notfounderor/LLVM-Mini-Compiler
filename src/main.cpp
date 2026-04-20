#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

int main() {
    std::string input = "x = 2 + 3 + 4;";

    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto ast = parser.parse();

    CodeGenContext context;

    // Create dummy main function
    auto funcType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(context.context), false);

    auto function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "main",
        context.module.get());

    auto block = llvm::BasicBlock::Create(context.context, "entry", function);
    context.builder.SetInsertPoint(block);

    ast->codegen(context);

    context.builder.CreateRet(
        llvm::ConstantInt::get(context.context, llvm::APInt(32, 0))
    );

    context.module->print(llvm::outs(), nullptr);

    return 0;
}
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
    ast->codegen(context);

    context.module->print(llvm::outs(), nullptr);

    return 0;
}
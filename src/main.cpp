#include <iostream>
#include <memory>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/GenericValue.h"

int main() {

    std::string input = "x = 2 + 3; y = x + 4;";

    // --------------------------
    // Lexer + Parser
    // --------------------------
    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto ast = parser.parse();

    CodeGenContext context;

    // --------------------------
    // LLVM INIT (IMPORTANT)
    // --------------------------
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    // --------------------------
    // Create main function
    // --------------------------
    auto funcType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(context.context), false);

    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "main",
        context.module.get());

    auto block = llvm::BasicBlock::Create(context.context, "entry", function);
    context.builder.SetInsertPoint(block);

    // --------------------------
    // Generate IR
    // --------------------------
    ast->codegen(context);

    context.builder.CreateRet(
        llvm::ConstantInt::get(context.context, llvm::APInt(32, 0))
    );

    // --------------------------
    // Verify IR
    // --------------------------
    if (llvm::verifyFunction(*function, &llvm::errs())) {
        std::cerr << "Function verification failed!\n";
        return 1;
    }

    // Print IR
    context.module->print(llvm::outs(), nullptr);

    // --------------------------
    // JIT EXECUTION
    // --------------------------
    std::string errStr;

    std::unique_ptr<llvm::Module> owner = std::move(context.module);

    llvm::ExecutionEngine* engine =
        llvm::EngineBuilder(std::move(owner))
        .setErrorStr(&errStr)
        .setEngineKind(llvm::EngineKind::JIT)
        .create();

    if (!engine) {
        std::cerr << "Failed to create ExecutionEngine: " << errStr << std::endl;
        return 1;
    }

    engine->finalizeObject();

    std::vector<llvm::GenericValue> noargs;

    llvm::GenericValue result = engine->runFunction(function, noargs);

    std::cout << "\nProgram executed successfully using JIT.\n";

    return 0;
}
# LLVM-Based Compiler with Optimization Passes

## Overview
A custom compiler built in C++ using LLVM, implementing a complete compilation pipeline including lexical analysis, parsing, AST construction, and LLVM IR generation. The project demonstrates core compiler design principles along with basic optimization techniques.

---

## Features

- **Lexer**: Tokenizes input source code into meaningful tokens  
- **Parser**: Builds an Abstract Syntax Tree (AST)  
- **AST Design**: Modular representation of expressions and control flow  
- **LLVM IR Generation**: Converts AST into LLVM Intermediate Representation  
- **Control Flow Support**:
  - `if` statements  
  - `while` loops  
- **Expressions**:
  - Arithmetic (`+`)  
  - Variables  
  - Comparisons (`>`, `<`)  

---

## Optimization Techniques

- **Constant Folding**  
  Evaluates constant expressions at compile time  
  Example:  
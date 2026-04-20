# LLVM-Based Compiler with Optimization Passes

## Overview
A custom compiler built in C++ using LLVM, implementing a full compilation pipeline from source code to execution. The project includes lexical analysis, parsing, AST construction, LLVM IR generation, optimization techniques, and JIT-based execution.

---

## Features

### Compiler Pipeline
- Lexical Analysis (Lexer)
- Parsing and AST construction
- LLVM IR generation
- JIT execution using LLVM

### Language Support
- Variables and assignments  
- Arithmetic expressions (`+`)  
- Comparison operators (`>`, `<`)  
- Control flow:
  - `if`
  - `while`

---

## Optimization Techniques

- **Constant Folding**  
  Evaluates constant expressions at compile time  
  Example: `2 + 3 → 5`

- **Dead Code Elimination**  
  Removes unreachable code branches  
  Example: `if (0) { ... }`

- **Loop Unrolling (Basic)**  
  Unrolls small loops (≤ 4 iterations) to reduce overhead  

---

## Execution (JIT)

The compiler uses LLVM’s **MCJIT Execution Engine** to execute generated code at runtime.

Pipeline:  
`Source Code → Lexer → Parser → AST → LLVM IR → JIT → Execution`

---

## Project Structure
llvm-compiler/
├── include/
│   ├── lexer.h
│   ├── parser.h
│   ├── ast.h
│   └── codegen.h
│
├── src/
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── ast.cpp
│   ├── codegen.cpp
│   └── main.cpp
│
├── test/
│   └── input.toy
│
├── CMakeLists.txt
└── README.md
---

## Example Input
x = 2 + 3;
y = x + 4;

if (0)
x = 100;

if (y > 5)
x = x + 1;

while (x < 3)
x = x + 1;

---

## Build & Run

### Prerequisites
- LLVM installed
- CMake
- C++17 compatible compiler



## Tech Stack
- C++
- LLVM (IR + MCJIT)
- CMake

## Key Learnings
- Compiler pipeline design (Lexer → Parser → AST → IR)
- Intermediate Representation (LLVM IR)
- AST-based optimizations
- Control flow generation using basic blocks
- Runtime execution using JIT compilation

## Future Improvements
- Function support
- Multi-statement parsing
- Advanced optimization passes
- Register allocation
- SSA transformations

## Inspiration
 ### Inspired by modern compiler infrastructures like LLVM and GPU-oriented compilation pipelines.

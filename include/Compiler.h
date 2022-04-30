#pragma once

#include <vector>
#include <optional>
#include <iostream>

#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

#include "Token.h"

namespace zpp {
    //The compiler takes the tokens. Parses them. (looks at what is given and expects recognizes combinations)
    //Uses the LLVM API to generate LLVM IR. (bytecode)
    //This bytecode can then be compiled to machine-code using CLang.
    class Compiler {
        private:
            std::vector<Token>::iterator currentToken;
            std::vector<Token>::iterator lastToken;
            llvm::LLVMContext llvmCtx;
            llvm::IRBuilder<>* llvmBuilder;
            llvm::Module* llvmModule;
        public:
            bool hasNextToken();
            bool hasNextToken(const TokenType& type);
            bool hasNextToken(const TokenType& type, const std::string& content);
            std::optional<Token> nextToken();
            std::optional<Token> nextToken(const TokenType& type);
            std::optional<Token> nextToken(const TokenType& type, const std::string& content);

            void compile(std::vector<Token> tokens);
    };
}
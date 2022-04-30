#pragma once

#include <vector>
#include <optional>
#include <iostream>
#include "Token.h"
namespace zpp {
    //The compiler takes the tokens. Parses them. (looks at what is given and expects recognizes combinations)
    //Uses the LLVM API to generate LLVM IR. (bytecode)
    //This bytecode can then be compiled to machine-code using CLang.
    class Compiler {
        private:
        std::vector<Token>::iterator currentToken;
        std::vector<Token>::iterator lastToken;
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
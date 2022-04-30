#pragma once
#include <vector>
#include <string>
#include "Token.h"
#include "StringHelper.h"
namespace zpp {
    class Tokenizer {
        public:
            Tokenizer() = default;
            //The tokenizer identifies words & symbols and categorizes them.
            //We have a token type for integer literals, floating point literals, string literals, operators, etc.
            //If we cannot categorize something, we just assume it is an "identifier". 
            //Identifiers are often variable names or function names.
            std::vector<Token> tokenize(std::string& sourceCode);
    };
}
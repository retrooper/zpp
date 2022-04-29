#pragma once
#include <vector>
#include <string>
#include "TokenSet.h"
#include "StringHelper.h"
namespace zpp {
    class Tokenizer {
        public:
            Tokenizer() = default;
            //The tokenizer identifies words & symbols. We group "tokens" on the a singular line together. 
            //So the amount of token sets indicates how many lines the file has.            
            std::vector<TokenSet> tokenize(std::string& sourceCode);
    };
}
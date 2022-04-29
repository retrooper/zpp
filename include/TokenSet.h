#pragma once
#include "Token.h"
#include <vector>
#include <iostream>

namespace zpp {
    //The reason we group tokens together is to easily store tokens on the same line.
    class TokenSet {
        public:
            TokenSet(uint32_t line);
            TokenSet(uint32_t line, std::vector<Token>);

            uint32_t line;
            std::vector<Token> tokens;
    };
}
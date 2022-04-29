#include "TokenSet.h"

namespace zpp {
    TokenSet::TokenSet(uint32_t line) {
        this->line = line;
    }

    TokenSet::TokenSet(uint32_t line, std::vector<Token> tokens) {
        this->line = line;
        this->tokens = tokens;
    }
}
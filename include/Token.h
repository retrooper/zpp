#pragma once

#include "TokenType.h"
#include <string>
namespace zpp {
    //A token should represent a symbol with a meaning. It can be a single operator or even a word. 
    //The token type structure helps us identify what kind of instruction this is. 
    //When parsing tokens, we need to look out for special combinations of tokens.
    //For example after an equals operator token, we can expect an integer literal. 
    //That means that an integer is being assigned to some variable.
    //The content string just contains the string representation of this symbol or word.
    //If it is an integer literal, we need to know its value.
    struct Token {
        TokenType type;
        std::string content;
        uint32_t lineNumber;
    };
}
#include "Tokenizer.h"
namespace zpp {
    static void addToken(TokenSet& tokenSet, Token& token) {
        tokenSet.tokens.push_back(token);
        token.type = TOKEN_TYPE_END;
        token.content.erase();
    }

    static bool isOtherOperator(const char& c) {
        switch (c) {
            case '{':
            case '}':
            case '(':
            case ')':
            case ',':
            case ';':
            case '*':
            case '/':
            case '+':
            case '[':
            case ']':
            case '!':
            case '<':
            case '>':
                return true;
            default:
                return false;
        }
    }

    static bool isDigit(const char& c) {
        switch (c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return true;
            default:
                return false;
        }
    }

    std::vector<TokenSet> Tokenizer::tokenize(std::string& sourceCode) {
        std::vector<TokenSet> tokenSets;
        std::vector<std::string> lines = StringHelper::split(sourceCode, "\n");
        for (uint32_t i = 0; i < lines.size(); i++) {
            std::string line = lines[i];
            uint32_t lineNumber = i + 1;
            TokenSet tokenSet(lineNumber);

            Token currentToken;
            for (char c : line) {
                //Is '0'->'9'
                if (isDigit(c)) {
                    //A digit as a new token or after an operator.
                    //Let us assume it is just an integer literal.
                    //We might correct it to a floating point later on.
                    if (currentToken.type == TOKEN_TYPE_END
                    || currentToken.type == TOKEN_TYPE_EQUALS_COMPARISON_OPERATOR
                    || currentToken.type == TOKEN_TYPE_EQUALS_OPERATOR) {
                        if (currentToken.type == TOKEN_TYPE_EQUALS_OPERATOR) {
                            addToken(tokenSet, currentToken);
                            std::cout << "added" << std::endl;
                        }
                        currentToken.type = TOKEN_TYPE_INTEGER_LITERAL;
                        currentToken.content += c;
                    }
                }
                else if (c == '.') {
                    //Support decimal shortcuts. For example: '.54'. In reality it is '0.54'.
                    if (currentToken.type == TOKEN_TYPE_END) {
                        currentToken.type == TOKEN_TYPE_FLOATING_POINT_LITERAL;
                        currentToken.content += c;
                    }
                    //Ordinary decimal. For example '3.53'
                    else if (currentToken.type == TOKEN_TYPE_INTEGER_LITERAL) {
                        //It was an integer, now we added a . right after.
                        currentToken.type = TOKEN_TYPE_FLOATING_POINT_LITERAL;
                        currentToken.content += c;
                    }
                    //Ignore if it is part of a string
                    else if (currentToken.type == TOKEN_TYPE_STRING_LITERAL) {
                        currentToken.content += c;
                    }
                }
                //We use spaces to end a token.
                else if (c == ' ') {
                    if (currentToken.type != TOKEN_TYPE_STRING_LITERAL) {
                        currentToken.type = TOKEN_TYPE_END;
                        addToken(tokenSet, currentToken);
                    }
                    else {
                        currentToken.content += " ";
                    }
                } 
                //First assume it is an equals operation. 
                //Later on we might correct it to a comparison check operator.
                else if (c == '=') {
                    if (currentToken.type != TOKEN_TYPE_EQUALS_OPERATOR) {
                        currentToken.type = TOKEN_TYPE_EQUALS_OPERATOR;
                        currentToken.content = '=';
                    }
                    else {
                        //Last token was already an equals operator. This must be a double equals.
                        currentToken.type = TOKEN_TYPE_EQUALS_COMPARISON_OPERATOR;
                        currentToken.content = "==";
                        addToken(tokenSet, currentToken);
                    }
                }
                else if (c == ';') {
                    if (currentToken.type != TOKEN_TYPE_STRING_LITERAL) {
                        currentToken.type = TOKEN_TYPE_END;
                        currentToken.content += c; 
                        addToken(tokenSet, currentToken);
                    }
                    else {
                        currentToken.content += c;
                    }
                }
                else if (isOtherOperator(c)) {
                    currentToken.type = TOKEN_TYPE_OTHER_OPERATOR;
                    currentToken.content += c;
                }
                else {
                    if (currentToken.type == TOKEN_TYPE_END 
                    || currentToken.type == TOKEN_TYPE_INTEGER_LITERAL
                    || currentToken.type == TOKEN_TYPE_FLOATING_POINT_LITERAL
                    || currentToken.type == TOKEN_TYPE_EQUALS_OPERATOR)
                    currentToken.type = TOKEN_TYPE_IDENTIFIER;
                    currentToken.content += c;
                }
            }
            addToken(tokenSet, currentToken);
        }
        return tokenSets;
    }
}
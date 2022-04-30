#include "Tokenizer.h"
namespace zpp {
    static void addToken(std::vector<Token>& tokens, Token& token) {
        if (token.type == TOKEN_TYPE_END && token.content == "") {
            return;
        }
        tokens.push_back(token);
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

    std::vector<Token> Tokenizer::tokenize(std::string& sourceCode) {
        std::vector<Token> tokens;
        std::vector<std::string> lines = StringHelper::split(sourceCode, "\n");
        for (uint32_t i = 0; i < lines.size(); i++) {
            std::string line = lines[i];
            Token token;
            token.type = TOKEN_TYPE_END;
            token.lineNumber = i + 1;
            for (char c : line) {
                //Is '0'->'9'
                if (isDigit(c)) {
                    //A digit as a new token or after an operator.
                    //Let us assume it is just an integer literal.
                    //We might correct it to a floating point later on.
                    if (token.type == TOKEN_TYPE_END
                    || token.type == TOKEN_TYPE_EQUALS_COMPARISON_OPERATOR
                    || token.type == TOKEN_TYPE_EQUALS_OPERATOR) {
                        if (token.type == TOKEN_TYPE_EQUALS_OPERATOR) {
                            addToken(tokens, token);
                        }
                        token.type = TOKEN_TYPE_INTEGER_LITERAL;
                        token.content += c;
                    }
                    else {
                        token.content += c;
                    }
                }
                else if (c == '.') {
                    //Support decimal shortcuts. For example: '.54'. In reality it is '0.54'.
                    if (token.type == TOKEN_TYPE_END) {
                        token.type == TOKEN_TYPE_FLOATING_POINT_LITERAL;
                        token.content += c;
                    }
                    //Ordinary decimal. For example '3.53'
                    else if (token.type == TOKEN_TYPE_INTEGER_LITERAL) {
                        //It was an integer, now we added a . right after.
                        token.type = TOKEN_TYPE_FLOATING_POINT_LITERAL;
                        token.content += c;
                    }
                    //Ignore if it is part of a string
                    else if (token.type == TOKEN_TYPE_STRING_LITERAL) {
                        token.content += c;
                    }
                }
                //We use spaces to end a token.
                else if (c == ' ') {
                    if (token.type != TOKEN_TYPE_STRING_LITERAL) {
                        addToken(tokens, token);
                    }
                    else {
                        token.content += " ";
                    }
                } 
                //First assume it is an equals operation. 
                //Later on we might correct it to a comparison check operator.
                else if (c == '=') {
                    if (token.type != TOKEN_TYPE_EQUALS_OPERATOR) {
                        token.type = TOKEN_TYPE_EQUALS_OPERATOR;
                        token.content = '=';
                    }
                    else {
                        //Last token was already an equals operator. This must be a double equals.
                        token.type = TOKEN_TYPE_EQUALS_COMPARISON_OPERATOR;
                        token.content = "==";
                        addToken(tokens, token);
                    }
                }
                else if (c == ';') {
                    if (token.type != TOKEN_TYPE_STRING_LITERAL) {
                        addToken(tokens, token);
                        token.type = TOKEN_TYPE_END_LINE;
                        token.content = ";";
                        addToken(tokens, token);
                    }
                    else {
                        token.content += c;
                    }
                }
                else if (isOtherOperator(c)) {
                    if (token.type == TOKEN_TYPE_IDENTIFIER && c == '(') {
                        token.type = TOKEN_TYPE_METHOD_SECTION;
                        token.content += c;

                    }
                    else if (token.type == TOKEN_TYPE_METHOD_SECTION && c == ')') {
                        token.content += c;
                        addToken(tokens, token);
                    }
                    else {
                        token.type = TOKEN_TYPE_OTHER_OPERATOR;
                        token.content += c;
                    }
                }
                else {
                    if (token.type == TOKEN_TYPE_END 
                    || token.type == TOKEN_TYPE_INTEGER_LITERAL
                    || token.type == TOKEN_TYPE_FLOATING_POINT_LITERAL
                    || token.type == TOKEN_TYPE_EQUALS_OPERATOR) {
                        token.type = TOKEN_TYPE_IDENTIFIER;
                    }
                    token.content += c;
                }
            }
            addToken(tokens, token);
        }
        return tokens;
    }
}
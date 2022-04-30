#include "Compiler.h"

namespace zpp {
    bool Compiler::hasNextToken() {
        return currentToken != lastToken;
    }

    bool Compiler::hasNextToken(const TokenType& type) {
        return nextToken(type).has_value();
    }

    bool Compiler::hasNextToken(const TokenType& type, const std::string& content) {
        return nextToken(type, content).has_value();
    }

    std::optional<Token> Compiler::nextToken() {
        if (!hasNextToken()) {
            return std::nullopt;
        }
        auto nextToken = currentToken;
        currentToken++;
        return *nextToken;
    }

    std::optional<Token> Compiler::nextToken(const TokenType& type) {
        if (!hasNextToken()) {
            return std::nullopt;
        }
        if (currentToken->type != type) {
            return std::nullopt;
        }
        return nextToken();
    }

    std::optional<Token> Compiler::nextToken(const TokenType& type, const std::string& content) {
        if (!hasNextToken()) {
            return std::nullopt;
        }
        if (currentToken->type != type) {
            return std::nullopt;
        }
        if (currentToken->content != content) {
            return std::nullopt;
        }
        return nextToken();
    }

    void Compiler::compile(std::vector<Token> tokens) {
        currentToken = tokens.begin();
        lastToken = tokens.end();

        while (hasNextToken()) {
            //Try detect methods
            auto identifier = nextToken(TOKEN_TYPE_IDENTIFIER);
            if (identifier.has_value()) {
                auto methodSection = nextToken(TOKEN_TYPE_METHOD_SECTION);
                if (methodSection.has_value()) {
                    std::string methodSectionStr = methodSection.value().content;
                    std::string methodName = methodSectionStr.substr(0, methodSectionStr.find('('));
                    std::cout << "name of method: " << methodName << std::endl;
                    if (hasNextToken(TOKEN_TYPE_OTHER_OPERATOR, "{")) {
                        auto potTk = nextToken();
                        if (potTk.has_value()) {
                            Token tk = potTk.value();
                            for (; tk.type != TOKEN_TYPE_OTHER_OPERATOR && tk.content != "}" && hasNextToken(); tk = nextToken().value()) {
                                //Function body code
                                std::cout << "Body token type: " << tk.type << ", body token content: " << tk.content << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
}
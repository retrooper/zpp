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
                        auto nt = nextToken();
                        if (nt.has_value()) {
                            Token tk = nt.value();
                            for (; tk.type != TOKEN_TYPE_OTHER_OPERATOR && tk.content != "}" && hasNextToken(); tk = nextToken().value()) {
                                //Function body code
                                if (nt.has_value() && nt.value().type == TOKEN_TYPE_IDENTIFIER) {
                                    if (nt.value().content == "i32") {
                                        //They are declaring a variable
                                        nt = nextToken(TOKEN_TYPE_IDENTIFIER);
                                        if (nt.has_value()) {
                                            std::string varName = nt.value().content;
                                            if (hasNextToken(TOKEN_TYPE_EQUALS_OPERATOR)) {
                                                nt = nextToken();
                                                if (nt.has_value() && nt.value().type == TOKEN_TYPE_INTEGER_LITERAL) {
                                                    int integerValue = std::stoi(nt.value().content);
                                                    if (hasNextToken(TOKEN_TYPE_END_LINE)) {
                                                        std::cout << "Var type: " << "i32, " << "Var name: " << varName << ", " << "Var int value: " << integerValue << std::endl;
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
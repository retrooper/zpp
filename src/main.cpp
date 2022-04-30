#include <iostream>
#include "SourcePreProcessor.h"
#include "Tokenizer.h"
#include "Compiler.h"
using namespace zpp;

    static const char* TOKEN_TYPE_MAP[] = {
        "TOKEN_TYPE_IDENTIFIER",
        "TOKEN_TYPE_STRING_LITERAL",
        "TOKEN_TYPE_INTEGER_LITERAL",
        "TOKEN_TYPE_FLOATING_POINT_LITERAL",
        "TOKEN_TYPE_EQUALS_OPERATOR",
        "TOKEN_TYPE_EQUALS_COMPARISON_OPERATOR",
        "TOKEN_TYPE_OTHER_OPERATOR",
        "TOKEN_TYPE_METHOD_SECTION",
        "TOKEN_TYPE_END_LINE",
        "TOKEN_TYPE_END"
    };
int main() {
    std::cout << "Welcome to the Z++ Compiler!" << std::endl;
    //First comes the pre-processing stage. Right now we just exclude comments from the source code.
    SourcePreProcessor preProcessor;
    std::ifstream sourceFile("tests/main.zpp");
    std::string sourceCode = preProcessor.process(sourceFile);
    //Now we tokenize the source code. The tokenizer identifies words & symbols and categorizes them.
    Tokenizer tokenizer;
    std::vector<Token> tokens = tokenizer.tokenize(sourceCode);
    for (Token token : tokens) {
        std::cout << "Token Type: " << TOKEN_TYPE_MAP[token.type] << ", Token content: " << token.content << std::endl;
    }
    //Now it is time to go through these categorized instructions and transform them into LLVM IR(bytecode) using the LLVM API.
    Compiler compiler;
    compiler.compile(tokens);
    return 0;
}

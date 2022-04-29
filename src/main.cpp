#include <iostream>
#include "SourcePreProcessor.h"
using namespace zpp;
int main() {
    std::cout << "Hello, World!" << std::endl;
    SourcePreProcessor preProcessor;
    std::ifstream sourceFile("tests/main.zpp");
    std::string sourceCode = preProcessor.process(sourceFile);
    std::cout << "Source code: " << sourceCode << std::endl;
    return 0;
}

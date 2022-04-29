#include "SourcePreProcessor.h"
namespace zpp {
    std::string SourcePreProcessor::process(std::ifstream& file) {
        std::string sourceCode;
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                //Filter out comments
                if (line.starts_with("#")) {
                    continue;    
                }
                sourceCode += line + "\n";
            }
        }
        file.close();
        return sourceCode;
    }
}
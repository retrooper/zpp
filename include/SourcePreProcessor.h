#pragma once
#include <fstream>
#include <filesystem>
#include <string>
namespace zpp {
    class SourcePreProcessor {
        public:
            SourcePreProcessor() = default;
            std::string process(std::ifstream& file);
    };
}
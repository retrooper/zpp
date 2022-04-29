#pragma once
#include <fstream>
#include <filesystem>
#include <string>
namespace zpp {
    class SourcePreProcessor {
        std::string process(std::ifstream file);
    };
}
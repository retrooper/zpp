#pragma once
#include <string>
#include <vector>
#include <iostream>
namespace zpp {
    namespace StringHelper {
        bool contains(std::string& target, const std::string& value);

        std::vector<std::string> split(std::string& target, const std::string& del = " ");
    }
}
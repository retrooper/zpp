#include "StringHelper.h"

namespace zpp {
    namespace StringHelper {
        bool contains(std::string& target, const std::string& value) {
            return target.find(value) != std::string::npos;
        }

        std::vector<std::string> split(std::string& target, const std::string& del) {
            std::vector<std::string> set;
            int start = 0;
            int end = target.find(del);
            while (end != -1) {
                std::string section = target.substr(start, end - start);
                set.push_back(section);
                start = end + del.size();
                end = target.find(del, start);
            }
            return set;
        }
    }
}
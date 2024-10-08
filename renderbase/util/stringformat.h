#pragma once
#include "common/config.h"
#include <string>
#include <stdint.h>
#include <set>
#include <map>
#include <vector>


class RENDERBASE_API StringFormat {
public:
    static std::string  int2string16(uint16_t i);
    static std::string  int2string(int i);
    static std::string	int2string64(uint64_t i);

    static std::string  vec2string(const std::vector<int>& values);
    static std::string  vec2string64(const std::vector<uint64_t>& values);
    static std::string  vec2string(const std::vector<std::string>& values);

    static std::string  set2string(const std::set<int>& values);
    static std::string  set2string64(const std::set<uint64_t>& values);
    static std::string  set2string(const std::set<std::string>& values);

    static uint16_t		str2uint16(const std::string& str);
    static uint32_t		str2uint32(const std::string& str);
    static uint64_t		str2uint64(const std::string& str);
};

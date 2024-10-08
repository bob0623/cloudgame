#include "stringformat.h"
#include <sstream>


std::string  StringFormat::int2string16(uint16_t i) {
    std::string str;
    std::stringstream ss;
    ss << i;
    ss >> str;
    return str;
}

std::string		StringFormat::int2string(int i) {
    std::string str;
    std::stringstream ss;
    ss << i;
    ss >> str;
    return str;
}

std::string		StringFormat::int2string64(uint64_t i) {
    std::string str;
    std::stringstream ss;
    ss << i;
    ss >> str;
    return str;
}

std::string  StringFormat::vec2string(const std::vector<int>& values) {
    std::string str;
    std::stringstream ss;
    bool first = true;
    for (auto it = values.begin(); it != values.end(); it++) {
        if (first) {
            ss << *it;
            first = false;
        }
        else {
            ss << "," << *it;
            first = false;
        }
    }
    ss >> str;
    return str;
}


std::string  StringFormat::vec2string64(const std::vector<uint64_t>& values) {
    std::string str;
    std::stringstream ss;
    bool first = true;
    for (auto it = values.begin(); it != values.end(); it++) {
        if (first) {
            ss << *it;
            first = false;
        }
        else {
            ss << "," << *it;
            first = false;
        }
    }
    ss >> str;
    return str;
}

std::string  StringFormat::vec2string(const std::vector<std::string>& values) {
    std::string str;
    std::stringstream ss;
    bool first = true;
    for (auto it = values.begin(); it != values.end(); it++) {
        if (first) {
            ss << *it;
            first = false;
        }
        else {
            ss << "," << *it;
            first = false;
        }
    }
    ss >> str;
    return str;
}


std::string  StringFormat::set2string(const std::set<int>& values) {
    std::string str;
    std::stringstream ss;
    bool first = true;
    for (auto it = values.begin(); it != values.end(); it++) {
        if (first) {
            ss << *it;
            first = false;
        }
        else {
            ss << "," << *it;
            first = false;
        }
    }
    ss >> str;
    return str;
}


std::string  StringFormat::set2string64(const std::set<uint64_t>& values) {
    std::string str;
    std::stringstream ss;
    bool first = true;
    for (auto it = values.begin(); it != values.end(); it++) {
        if (first) {
            ss << *it;
            first = false;
        }
        else {
            ss << "," << *it;
            first = false;
        }
    }
    ss >> str;
    return str;
}

std::string  StringFormat::set2string(const std::set<std::string>& values) {
    std::string str;
    std::stringstream ss;
    bool first = true;
    for (auto it = values.begin(); it != values.end(); it++) {
        if (first) {
            ss << *it;
            first = false;
        }
        else {
            ss << "," << *it;
            first = false;
        }
    }
    ss >> str;
    return str;
}

uint16_t	StringFormat::str2uint16(const std::string& str) {
    uint16_t val = 0;
    std::stringstream ss;
    ss << str;
    ss >> val;
    return val;
}

uint32_t	StringFormat::str2uint32(const std::string& str) {
    uint32_t val = 0;
    std::stringstream ss;
    ss << str;
    ss >> val;
    return val;
}





uint64_t	StringFormat::str2uint64(const std::string& str) {
    uint64_t val = 0;
    std::stringstream ss;
    ss << str;
    ss >> val;
    return val;
}


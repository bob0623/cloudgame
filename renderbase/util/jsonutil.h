#pragma once

#include "common/config.h"
#include "json/json.h"
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

class RENDERBASE_API JsonUtil {
public:
    //unserialize
    static std::string      getJsonString(const Json::Value& value);
    static uint16_t         getJsonUInt16(const Json::Value& value);
    static uint32_t         getJsonUInt32(const Json::Value& value);
    static uint64_t         getJsonUInt64(const Json::Value& value);

    //serialize
    static std::string      toString(const Json::Value& value);
    static std::string      toString(const std::map<uint64_t, uint64_t> values);
    static std::string      toString(const std::map<std::string, Json::Value> values);
    static std::string      toString(const std::map<std::string, std::string> values);

    static std::map<std::string, Json::Value>    fromString(const std::string& value);

    static Json::Value    fromStringToValue(const std::string& value);
};


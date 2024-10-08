#include "jsonutil.h"
#include "stringformat.h"

std::string JsonUtil::getJsonString(const Json::Value& value) {
	if (value.empty()) {
		return "";
	}

	std::string ret;
	switch (value.type()) {
	case Json::stringValue:
		ret = value.asString();
		break;
	case Json::intValue:
		ret = StringFormat::int2string(value.asInt());
		break;
	case Json::uintValue:
		ret = StringFormat::int2string(value.asUInt());
		break;
	default:
		ret = "";
		break;
	}
	return ret;
}

uint16_t JsonUtil::getJsonUInt16(const Json::Value& value) {
	if (value.empty())
		return 0;
	uint32_t ret = 0;
	switch (value.type()) {
	case Json::stringValue:
		ret = StringFormat::str2uint16(value.asString());
		break;
	case Json::intValue:
		ret = (uint16_t)value.asInt();
		break;
	case Json::uintValue:
		ret = (uint16_t)value.asUInt();
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

uint32_t JsonUtil::getJsonUInt32(const Json::Value& value) {
	if (value.empty())
		return 0;
	uint32_t ret = 0;
	switch (value.type()) {
	case Json::stringValue:
		ret = StringFormat::str2uint32(value.asString());
		break;
	case Json::intValue:
		ret = (uint32_t)value.asInt();
		break;
	case Json::uintValue:
		ret = value.asUInt();
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

uint64_t JsonUtil::getJsonUInt64(const Json::Value& value) {
	if (value.empty())
		return 0;
	uint64_t ret = 0;
	switch (value.type()) {
	case Json::stringValue:
		ret = StringFormat::str2uint64(value.asString());
		break;
	case Json::intValue:
		ret = (uint64_t)(value.asInt());
		break;
	case Json::uintValue:
		ret = value.asUInt64();
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

std::string 	JsonUtil::toString(const Json::Value& value) {
	//Json::StyledWriter writer;
	//return writer.write(value);
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "";
	return Json::writeString(builder, value);
}

std::string      JsonUtil::toString(const std::map<uint64_t, uint64_t> values) {
	Json::Value node;

	for (std::map<uint64_t, uint64_t>::const_iterator it = values.begin(); it != values.end(); it++) {
		Json::Value nodeItem;
		nodeItem[StringFormat::int2string64(it->first)] = Json::Value((Json::UInt64)it->second);
		node.append(nodeItem);
	}
	return toString(node);
}

std::string      JsonUtil::toString(const std::map<std::string, Json::Value> values) {
	Json::Value node;

	for (std::map<std::string, Json::Value>::const_iterator it = values.begin(); it != values.end(); it++) {
		Json::Value nodeItem;
		nodeItem[it->first] = it->second;
		node.append(nodeItem);
	}
	return toString(node);
}

std::string      JsonUtil::toString(const std::map<std::string, std::string> values) {
	Json::Value node;

	for (std::map<std::string, std::string>::const_iterator it = values.begin(); it != values.end(); it++) {
		Json::Value nodeItem;
		nodeItem[it->first] = it->second;
		node.append(nodeItem);
	}
	return toString(node);
}

std::map<std::string, Json::Value>	JsonUtil::fromString(const std::string& value) {
	std::map<std::string, Json::Value> ret;

	Json::Reader reader;
	Json::Value root;
	reader.parse(value.c_str(), root);
	Json::Value::Members members = root.getMemberNames();
	for (Json::Value::Members::iterator it = members.begin(); it != members.end(); it++) {
		std::string key = (*it);
		Json::Value value = root[key];
		ret[key] = value;
	}

	return ret;
}

Json::Value	JsonUtil::fromStringToValue(const std::string& value) {

	Json::Reader reader;
	Json::Value ret;
	reader.parse(value.c_str(), ret);
	return ret;
}

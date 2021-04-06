#pragma once

#include "core/Util.hpp"
#include <sstream>
#include <algorithm>

Json::Json() {

}

void Json::AddPair(const std::string& key, const std::string& value) {
	m_data[key] = value;
}

bool Json::HasKey(const std::string& key) {
	for (auto it : m_data) {
		if (it.first == key) {
			return true;
		}
	}
	return false;
}

std::string& Json::GetValue(const std::string& key) {
	return m_data[key];
}

Json::operator std::string() const {
	std::string out = "{";
	for (auto[attribute, value] : m_data) {
		out += "\"" + attribute + "\":\"" + value + "\",";
	}
	out.pop_back();
	out += "}";
	return out;
}

Json Util::JsonParse(std::string& data) {
	Json out;
	
	data = data.substr(0, data.find("}"));

	data.erase(std::remove(data.begin(), data.end(), '{'), data.end());
	data.erase(std::remove(data.begin(), data.end(), '}'), data.end());
	data.erase(std::remove(data.begin(), data.end(), '"'), data.end());
	

	std::stringstream ss(data);
	std::string section;

	while (std::getline(ss, section, ',')) {
		size_t loc = section.find(":");

		out.AddPair(section.substr(0, loc), section.substr(loc + 1));
	}

	return out;
}

bool isWhitespace(char c) {
	if ((unsigned int)c == 0u) {
		return true;
	}
	return false;
}

std::string Util::Trim(const std::string& str) {
	std::string s = str;
	s.erase(remove_if(s.begin(), s.end(), isWhitespace), s.end());
	return s;
}
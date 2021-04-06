#pragma once
#include <string>
#include <unordered_map>

class Json {
private:
	std::unordered_map<std::string, std::string> m_data;
public:
	Json();
	void AddPair(const std::string& key, const std::string& value);
	bool HasKey(const std::string& key);
	std::string& GetValue(const std::string& key);

	operator std::string() const;
};

class Util {
public:
	static Json JsonParse(std::string& data);
	static std::string Trim(const std::string& str);
};
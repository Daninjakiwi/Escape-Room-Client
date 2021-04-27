#pragma once
#include <string>
#include <unordered_map>
#include <util/maths/Vector.hpp>

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
	static std::string VectorToString(volt::Vec3 vec);
	static volt::Vec3 StringToVector(const std::string& str);
};
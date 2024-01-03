#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <variant>


namespace ini
{
	using value = std::variant<int, float, bool, std::string>;
	using section = std::map<std::string, value>;

	class document
	{
	public:
		bool parse(const std::vector<char>& data);

		section operator[](const std::string& sKey);
		section at(const std::string& sKey) const;

		std::map<std::string, section>::iterator begin();
		std::map<std::string, section>::iterator end();

		std::map<std::string, section>::const_iterator begin() const;
		std::map<std::string, section>::const_iterator end() const;

	private:
		std::map<std::string, section> m_sections;
	};



	namespace impl 
	{
		std::vector<char> readStreamToVector(std::istream& stream);
		value getValue(const std::string& str);
	}
}


template<typename Stream>
Stream& operator >> (Stream& stream, ini::document& doc)
{
	auto data = ini::impl::readStreamToVector(stream);
	doc.parse(data);
	return stream;
}
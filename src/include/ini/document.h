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

		using sections = std::map<std::string, section>;

		sections::iterator begin();
		sections::iterator end();

		sections::const_iterator begin() const;
		sections::const_iterator end() const;

	private:
		 sections m_sections;
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
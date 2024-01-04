#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <variant>



namespace ini
{
	using value = std::variant<int, double, bool, std::string>;
	using section = std::map<std::string, value>;

	class document
	{
	public:
		section operator[](const std::string& sKey);
		section at(const std::string& sKey) const;

		using sections = std::map<std::string, section>;

		sections::iterator begin();
		sections::iterator end();

		sections::const_iterator begin() const;
		sections::const_iterator end() const;

	private:
		sections m_sections;
		bool parse(const std::vector<char>& data);

		// Operators for input and output
		friend std::istream& operator >> (std::istream& stream, ini::document& doc);
	};

	std::istream& operator >> (std::istream& stream, ini::document& doc);
}

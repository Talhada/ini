#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <variant>



namespace ini
{
	using value = std::variant<std::string, int, double, bool>;
	using section = std::map<std::string, value>;

	class document
	{
	public:
		section& operator[](const std::string& sKey);
		const section& at(const std::string& sKey) const;

		using sections = std::map<std::string, section>;

		sections::iterator begin();
		sections::iterator end();

		sections::const_iterator begin() const;
		sections::const_iterator end() const;

		std::string toString() const;
		bool fromString(const std::string& data);
	private:
		sections m_sections;
	};

	std::istream& operator >> (std::istream& stream, ini::document& doc);
	std::ostream& operator << (std::ostream& stream, ini::document& doc);
}

#include <ini/document.h>
#include <algorithm>

namespace ini
{
	namespace impl
	{
		std::string readStream(std::istream& stream)
		{
			// Create an empty vector
			std::string data;

			// Use istreambuf_iterator to read the stream from the beginning (streambuf())
			// to the end of the stream and back-insert into the vector.
			std::copy(std::istreambuf_iterator<char>(stream),
				std::istreambuf_iterator<char>(),
				std::back_inserter(data));

			return data;
		}

		// Function to convert string to lowercase
		std::string toLower(const std::string& str)
		{
			std::string lowerStr = str;
			std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
				[](unsigned char c) { return std::tolower(c); });
			return lowerStr;
		}

		// Function to trim whitespace from both ends of a string
		std::string trim(const std::string& str, const char c = ' ')
		{
			size_t first = str.find_first_not_of(c);
			if (first == std::string::npos)
				return ""; // No non-space characters

			size_t last = str.find_last_not_of(c);
			return str.substr(first, (last - first + 1));
		}

		bool isTrue(const std::string& str)
		{
			auto _str = toLower(trim(str));
			return _str == "true";
		}

		bool isFalse(const std::string& str)
		{
			auto _str = toLower(trim(str));
			return _str == "false";
		}

		ini::value getValue(const std::string& str)
		{
			std::istringstream iss(str);
			int intValue;
			double doubleValue;

			// Check for integer
			if (iss >> intValue && iss.eof())
				return intValue;

			// Reset the stream state and position
			iss.clear();
			iss.seekg(0, std::ios::beg);

			// Check for double
			if (iss >> doubleValue && iss.eof())
				return doubleValue;

			if (isTrue(str))
				return true;

			if (isFalse(str))
				return false;

			// If neither integer nor float, it's a string
			return str;
		}

	}




	bool document::fromString(const std::string& data)
	{
		std::string section_name, var_name, var_value;
		section s;
		std::string* pCurrent = &var_name;

		bool stringOpen = false;
		bool isComment = false;

		for (const auto c : data)
		{
			if (c == '[')
			{
				// Open new section
				section_name.clear();

				// Write to section name
				pCurrent = &section_name;
			}
			else if (c == ']')
			{
				// Close section
				m_sections[section_name] = s;

				var_name.clear();
				pCurrent = &var_name;
			}
			else if (c == '=')
			{
				var_value.clear();
				
				while(!pCurrent->empty() && pCurrent->back() == ' ')
					pCurrent->pop_back();

				pCurrent = &var_value;
			}
			else if (c == '\n')
			{
				// Add value to the map
				if (!var_name.empty())
					m_sections[section_name][var_name] = impl::getValue(var_value);

				// Clear and point to var name
				var_value.clear();
				var_name.clear();

				pCurrent = &var_name;

				// Must reset comment state
				isComment = false;
			}
			else if (c == '"')
			{
				stringOpen = !stringOpen;
			}
			else if (c == ';')
			{
				isComment = true;
			}
			else
			{
				if (!isComment)
				{
					if (!(pCurrent->empty() && c == ' ') || stringOpen)
						pCurrent->push_back(c);
				}
			}
		}

		// Add last value if any before finishing parse
		if (!var_name.empty() && !var_value.empty())
			m_sections[section_name][var_name] = impl::getValue(var_value);

		return true;
	}

	ini::section& document::operator[](const std::string& sKey)
	{
		return m_sections[sKey];
	}

	document::sections::const_iterator document::end() const
	{
		return m_sections.end();
	}

	document::sections::iterator document::end()
	{
		return m_sections.end();
	}

	std::string document::toString() const
	{
		std::ostringstream result;
		for (const auto& pair : m_sections)
		{
			// Write section header
			result << '[' << pair.first << ']';
			result << '\n';

			// Write values
			for (const auto& val : pair.second)
			{
				result << val.first << '=';
				std::visit([&result](auto&& arg) { result << arg; }, val.second);
				result << '\n';
			}
			result << '\n';
		}

		return result.str();
	}

	const ini::section& document::at(const std::string& sKey) const
	{
		return m_sections.at(sKey);
	}

	document::sections::const_iterator document::begin() const
	{
		return m_sections.begin();
	}

	document::sections::iterator document::begin()
	{
		return m_sections.begin();
	}

	// Generic parsing
	std::istream& operator>>(std::istream& stream, ini::document& doc)
	{
		auto data = ini::impl::readStream(stream);
		doc.fromString(data);
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, document& doc)
	{
		stream << doc.toString();
		return stream;
	}

}
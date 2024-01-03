#include <ini/document.h>

namespace ini
{
	bool document::parse(const std::vector<char>& data)
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

		return true;
	}

	ini::section document::operator[](const std::string& sKey)
	{
		return m_sections[sKey];
	}

	std::map<std::string, ini::section>::const_iterator document::end() const
	{
		return m_sections.end();
	}

	std::map<std::string, section>::iterator document::end()
	{
		return m_sections.end();
	}

	ini::section document::at(const std::string& sKey) const
	{
		return m_sections.at(sKey);
	}

	std::map<std::string, ini::section>::const_iterator document::begin() const
	{
		return m_sections.begin();
	}

	std::map<std::string, section>::iterator document::begin()
	{
		return m_sections.begin();
	}



	namespace impl
	{
		std::vector<char> readStreamToVector(std::istream& stream)
		{
			// Create an empty vector
			std::vector<char> data;

			// Use istreambuf_iterator to read the stream from the beginning (streambuf())
			// to the end of the stream and back-insert into the vector.
			std::copy(std::istreambuf_iterator<char>(stream),
				std::istreambuf_iterator<char>(),
				std::back_inserter(data));

			return data;
		}

		ini::value getValue(const std::string& str)
		{
			std::istringstream iss(str);
			int intValue;
			float floatValue;

			// Check for integer
			if (iss >> intValue && iss.eof())
				return intValue;

			// Reset the stream state and position
			iss.clear();
			iss.seekg(0, std::ios::beg);

			// Check for float
			if (iss >> floatValue && iss.eof())
				return floatValue;

			if (str == "true" || str == "True" || str == "TRUE")
				return true;

			if (str == "false" || str == "False" || str == "FALSE")
				return false;

			// If neither integer nor float, it's a string
			return str;
		}

	}
}
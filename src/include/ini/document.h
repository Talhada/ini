#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>

namespace ini
{
	using section = std::map<std::string, std::string>;

	class document
	{
	public:

		bool parse(const std::vector<char>& data)
		{
			std::string section_name, var_name, var_value;
			section s;
			std::string* pCurrent = &var_name;

			const std::set<char> ignore = {'\r', ' '};

			for (const auto c : data)
			{
				if (ignore.count(c))
					continue;

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
					pCurrent = &var_value;
				}
				else if (c == '\n')
				{
					if (!var_name.empty())
						m_sections[section_name][var_name] = var_value;

					var_value.clear();
					var_name.clear();

					pCurrent = &var_name;
				}
				else
				{
					pCurrent->push_back(c);
				}
			}

			return true;
		}

		section operator[](const std::string& sKey) { return m_sections[sKey]; }


	private:
		std::map<std::string, section> m_sections;
	};



	namespace impl 
	{
		std::vector<char> readStreamToVector(std::istream& stream) {
			// Create an empty vector
			std::vector<char> data;

			// Use istreambuf_iterator to read the stream from the beginning (streambuf())
			// to the end of the stream and back-insert into the vector.
			std::copy(std::istreambuf_iterator<char>(stream),
				std::istreambuf_iterator<char>(),
				std::back_inserter(data));

			return data;
		}
	}

}


template<typename Stream>
Stream& operator >> (Stream& stream, ini::document& doc)
{
	auto data = ini::impl::readStreamToVector(stream);
	doc.parse(data);
	return stream;
}
#include <fstream>
#include <iostream>

#include <ini/document.h>

int main()
{
	std::ifstream stream("sample_1.ini");

	if (stream.bad())
		return 1;

	// Create document instance
	ini::document doc;

	// Read and parse from stream
	stream >> doc;

	// Get hostname
	auto port = std::get<int>(doc["database"]["port"]);
	auto host =  std::get<std::string>(doc["database"]["host"]);
	auto isAdmin = std::get<bool>(doc["user"]["isAdmin"]);

	// Iterate all sections
	for (const auto& s : doc)
	{
		std::cout << "Section name: " << s.first << std::endl;
		for (const auto& pair : s.second)
		{
			std::cout << "Var --> " << pair.first << " : ";

			// Visit the value with auto
			std::visit([](auto&& arg) { std::cout << arg; }, pair.second); 
			
			std::cout << std::endl;
		}
	}

	return 0;
}
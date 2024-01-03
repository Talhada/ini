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
	auto db =  doc["database"]["host"];


	// Iterate all sections
	for (const auto& s : doc)
	{
		std::cout << "Section name: " << s.first << std::endl;
		for (const auto& pair : s.second)
		{
			std::cout << "Var --> " << pair.first << " : " << pair.second << std::endl;
		}
	}

	return 0;
}
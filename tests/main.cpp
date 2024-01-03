#include <fstream>

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

	return 0;
}
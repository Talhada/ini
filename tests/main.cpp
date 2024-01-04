#include <sstream>
#include <gtest/gtest.h>

#include <ini/document.h>

TEST(IniParse, ParseGlobal)
{
	std::stringstream ss;
	ss << "var=2"; // The simplest file you can have

	// Parse
	ini::document doc;
	ss >> doc;

	auto value = std::get<int>(doc[""]["var"]);
	EXPECT_EQ(2, value);
}

TEST(IniParse, ParseSection)
{
	std::stringstream ss;
	ss << "[Section1]\nvar=true";

	// Parse
	ini::document doc;
	ss >> doc;

	auto value = std::get<bool>(doc["Section1"]["var"]);
	EXPECT_TRUE(value);
}

TEST(IniParse, ParseSections)
{
	std::stringstream ss;
	ss << "[Section1]\nvar=true\n[Section2]\nvar=false";

	// Parse
	ini::document doc;
	ss >> doc;

	auto value1 = std::get<bool>(doc["Section1"]["var"]);
	auto value2 = std::get<bool>(doc["Section2"]["var"]);
	EXPECT_TRUE(value1);
	EXPECT_FALSE(value2);
}

TEST(IniParse, ParseString)
{
	std::stringstream ss;
	ss << "[Section1]\nvar=Some Text";

	// Parse
	ini::document doc;
	ss >> doc;

	auto value = std::get<std::string>(doc["Section1"]["var"]);
	EXPECT_STREQ("Some Text", value.c_str());
}

TEST(IniParse, ParseQuotedString)
{
	std::stringstream ss;
	ss << "[Section1]\nvar=\"Some Quoted Text\"";

	// Parse
	ini::document doc;
	ss >> doc;

	auto value = std::get<std::string>(doc["Section1"]["var"]);
	EXPECT_STREQ("Some Quoted Text", value.c_str());
}

TEST(IniParse, ParseInt)
{
	std::stringstream ss;
	ss << "[Section1]\nvar=356";

	// Parse
	ini::document doc;
	ss >> doc;

	auto value = std::get<int>(doc["Section1"]["var"]);
	EXPECT_EQ(356, value);
}

TEST(IniParse, ParseFloat)
{
	std::stringstream ss;
	ss << "[Section1]\nvar=354.36";

	// Parse
	ini::document doc;
	ss >> doc;

	auto value = std::get<double>(doc["Section1"]["var"]);
	EXPECT_DOUBLE_EQ(354.36, value);
}

TEST(IniParse, ParseIgnoreComments)
{
	std::stringstream ss;
	ss << ";This is a comment\n[Section1]\n;This is another comment\nvar=354.36";

	// Parse
	ini::document doc;
	ss >> doc;

	auto value = std::get<double>(doc["Section1"]["var"]);
	EXPECT_DOUBLE_EQ(354.36, value);
}

//int main()
//{
//	std::ifstream stream("sample_1.ini"); 
//
//	if (stream.bad())
//		return 1;
//
//	// Create document instance
//	ini::document doc;
//
//	// Read and parse from stream
//	stream >> doc;
//
//	// Get hostname
//	auto port = std::get<int>(doc["database"]["port"]);
//	auto host =  std::get<std::string>(doc["database"]["host"]);
//	auto isAdmin = std::get<bool>(doc["user"]["isAdmin"]);
//
//	// Iterate all sections
//	for (const auto& s : doc)
//	{
//		std::cout << "Section name: " << s.first << std::endl;
//		for (const auto& pair : s.second)
//		{
//			std::cout << "Var --> " << pair.first << " : ";
//
//			// Visit the value with auto
//			std::visit([](auto&& arg) { std::cout << arg; }, pair.second); 
//			
//			std::cout << std::endl;
//		}
//	}
//
//	return 0;
//}

int main(int argc, char** argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
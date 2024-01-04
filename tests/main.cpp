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



TEST(IniToString, Convert)
{
	ini::document doc;
	doc["Section1"]["StringValue"] = std::string("Some Text");
	doc["Section1"]["IntValue"] = 123;
	doc["Section1"]["DoubleValue"] = 5.658;

	std::ostringstream os;
	os << doc;
	auto str = os.str();

	auto pos = str.find("Section1");
	EXPECT_GT(pos, 0);

	pos = str.find("IntValue");
	EXPECT_GT(pos, 0);

	pos = str.find("StringValue");
	EXPECT_GT(pos, 0);

	pos = str.find("DoubleValue");
	EXPECT_GT(pos, 0);
}

TEST(IniToString, ConvertBack)
{
	ini::document doc, doc2;
	doc["Section1"]["StringValue"] = std::string("Some Text");

	std::stringstream ss;
	ss << doc;
	ss >> doc2;

	auto value = std::get<std::string>(doc2["Section1"]["StringValue"]);
	EXPECT_STREQ("Some Text", value.c_str());
}

int main(int argc, char** argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
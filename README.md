# INI Document Parser and Generator


## Overview

This modern C++ library facilitates parsing and generating INI (Initialization File) documents. It supports reading INI files into a structured format and writing modifications back to files or strings.

## Build Status
[![CMake on multiple platforms](https://github.com/Talhada/ini/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Talhada/ini/actions/workflows/cmake-multi-platform.yml)

## Features

- Parse INI Files: Converts INI file content into a structured, easy-to-manipulate format.
- Generate INI Content: Create and modify INI content programmatically.
- Data Types Support: Handles strings, integers, doubles, and booleans.

## Usage

### Parsing INI Files

To parse an INI file, use the fromString method of the document class.

```cpp
ini::document doc;
std::string iniContent = "your INI content here";
doc.fromString(iniContent);
```

Or for conveninence you can use the ">>" operator

```cpp
std::ifstream ff ("someFile.ini");
ini::document doc;
ff >> doc;
```

### Accessing Data

You can access the parsed data using the [] operator.

```cpp
// Accessing a string value
std::string stringValue = std::get<std::string>(doc["section"]["stringKey"]);

// Accessing an integer value
int intValue = std::get<int>(doc["section"]["intKey"]);

// Accessing a double value
double doubleValue = std::get<double>(doc["section"]["doubleKey"]);

// Accessing a boolean value
bool boolValue = std::get<bool>(doc["section"]["boolKey"]);
```

### Iterating through the INI File

You can iterate over sections and key-value pairs in the document.

```cpp
for (const auto& sectionPair : doc) {
const auto& sectionName = sectionPair.first;
const auto& section = sectionPair.second;

    std::cout << "Section: " << sectionName << std::endl;

    for (const auto& keyValue : section) {
        const auto& key = keyValue.first;
        const auto& value = keyValue.second;

        std::cout << "Key: " << key << ", Value: ";
        std::visit([](auto&& arg) { std::cout << arg; }, value);
        std::cout << std::endl;
    }

}
```

## Generating INI Content

To generate INI content, use the toString method.

```cpp
std::string iniOutput = doc.toString();
```

You can also use the "<<" operator for streams

```cpp
ini::document doc;
doc["section"]["var"] = 3;

std::fstream ff;
ff << doc;
```

# Installation

TODO

# Contributing

Contributions are welcome. Please follow the standard fork, branch, and pull request workflow.

# License

Licensed under the MIT License.

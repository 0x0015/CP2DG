#pragma once
#include <iostream>
#include <vector>
#include <filesystem>

void parse(std::vector<std::filesystem::path>* doneFiles, std::vector<std::string>* systemIncludes, std::string* outString, std::filesystem::path inputFilename, std::filesystem::path currentPath);

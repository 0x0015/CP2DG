#pragma once
#include <iostream>
#include <filesystem>

std::string getCWD();

void deleteFile(std::string path);
void copyFile(std::string path1, std::string path2);
void createFolder(std::string path);

bool fileExists(std::string path);

#pragma once
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

string readFile(string filename);

void writeFile(string filename, string content);

#include "fileManipulation.hpp"
#include "getExecutablePath.hpp"

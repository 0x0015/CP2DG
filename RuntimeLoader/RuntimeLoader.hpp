#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

class CP2DG;

class RuntimeLoader{
public:
	CP2DG* mainWindow;
	std::string buildDir = "Runtime";
	std::string sourceDir = "Plugins";
	std::vector<std::string> errors;
	bool build();
	void deleteCache();
	RuntimeLoader(CP2DG* mw);
};


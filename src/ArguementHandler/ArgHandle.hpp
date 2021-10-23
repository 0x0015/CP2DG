#pragma once
#include <iostream>
#include <vector>
#include "Arguement.hpp"

using namespace std;

class ArguementHandler{
	public:
		vector<Arguement> args;
		vector<int> searchStringVector(vector<string> v, string q);
		void printArgs();
		vector<Arguement> findArgs(string type);
		bool hasArg(string type);
		ArguementHandler(int argc, char* argv[]);
};

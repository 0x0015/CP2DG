#pragma once
#include <iostream>
#include <optional>
#include <vector>
#include <zip.h>


class Zip{
public:
	bool readable = false;
	zip_t* za;
	zip_source_t* src;
	zip_error_t error;
	int err = 0;
private:
public:
	Zip(std::string filename);
	Zip(unsigned char* data, unsigned int len);
	std::optional<std::pair<char*, int>> readFile(std::string filename);
	std::optional<FILE*> readFILE(std::string filename);
	bool writeFileToDisk(std::string sourceFilename, std::string destination);
	std::vector<std::string> listFiles();
	~Zip();
};

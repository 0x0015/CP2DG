#include "zip.hpp"
#include <zip.h>
#include <ostream>
#include <fstream>
#include <filesystem>
#include "../SimpleCppTextFileHandler/file.hpp"

Zip::Zip(std::string filename){
	int err = 0;
	za = zip_open(filename.c_str(), ZIP_RDONLY, &err);
	if(err != 0 || za == NULL){
		readable = false;
		return;
	}
	readable = true;
}

Zip::Zip(unsigned char* data, unsigned int len){
	zip_error_init(&error);
	src = zip_source_buffer_create(data, len, 1, &error);
	if(src == NULL){
		readable = false;
		return;
	}
	za = zip_open_from_source(src, ZIP_RDONLY, &error);
	if(za == NULL){
		readable = false;
		return;
	}
	readable = true;
}

std::optional<std::pair<char*, int>> Zip::readFile(std::string filename){//in this scenario it is up to you to delete[] the returned buffer
	if(!readable){
		return(std::nullopt);
	}
	zip_stat_t st;
	zip_stat_init(&st);
	zip_stat(za, filename.c_str(), 0, &st);
	zip_file_t* file_program = zip_fopen(za, filename.c_str(), 0);
	if(file_program == NULL){
		return(std::nullopt);
	}
	char* contents = new char[st.size];
	int size = st.size;
	zip_fread(file_program, contents, size);
	zip_fclose(file_program);
	return(std::pair<char*, int>(contents, size));
}
std::optional<FILE*> Zip::readFILE(std::string filename){
	std::optional<std::pair<char*, int>> file = readFile(filename);
	if(!file){
		return(std::nullopt);
	}
	FILE* FILEstream = fmemopen(file.value().first, file.value().second, "r");
	return(FILEstream);
}

bool Zip::writeFileToDisk(std::string sourceFilename, std::string destination){
	std::optional<std::pair<char*, int>> file = readFile(sourceFilename);
	if(!file){
		return(false);
	}
	//yay stackoverflow
	std::filesystem::path writePath(destination);
	std::filesystem::path parentPath = writePath.parent_path();
	std::string sparentPath = parentPath.string();

	if(!fileExists(sparentPath)){
		createFolder(sparentPath);
	}

	std::ofstream binFile(destination, std::ios::out | std::ios::binary);//wow, the c++ way of doing things
	binFile.write(file.value().first, file.value().second);
	binFile.close();
	return(true);
}

std::vector<std::string> Zip::listFiles(){
	if(!readable){
		return(std::vector<std::string>());
	}
	std::vector<std::string> entries;
	int totalEntries = zip_get_num_entries(za, 0);
	for(int i=0;i<totalEntries;i++){
		const char* fn = zip_get_name(za, i, 0);
		if(fn != NULL){
			std::string filename = std::string(fn);
			entries.push_back(filename);
		}
	}
	return(entries);
}

Zip::~Zip(){
	if(readable && za != NULL){
		zip_discard(za);
	}
}

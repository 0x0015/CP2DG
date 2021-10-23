#include "fileManipulation.hpp"

std::string getCWD(){
	return(std::filesystem::current_path().string());
}

void deleteFile(std::string path){
	std::filesystem::remove_all(path);
}
void copyFile(std::string path1, std::string path2){
	std::filesystem::copy(path1, path2);
}
void createFolder(std::string path){
	std::filesystem::create_directories(path);
}

bool fileExists(std::string path){
	return(std::filesystem::exists(path));
}

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <filesystem>
#include "ArguementHandler/ArgHandle.hpp"
#include "SimpleCppTextFileHandler/file.hpp"
#include "main.hpp"

//https://thispointer.com/find-all-occurrences-of-a-sub-string-in-a-string-c-both-case-sensitive-insensitive/
void findAllOccurances(std::vector<size_t> & vec, std::string& data, std::string toSearch)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Add position to the vector
        vec.push_back(pos);
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + toSearch.size());
    }
}

std::pair<std::string, int> findNextChar(std::string& data, size_t position){
	for(int i=position;i<data.length();i++){
		std::string let = data.substr(i, 1);
		if(let != " " && let != "\n" && let != "\t"){
			return(std::pair<std::string, int>(let, i));
		}
	}
	return(std::pair<std::string, int>("", -1));
}

int findNextOccurenceChar(std::string& data, size_t position, std::string what){
	for(int i=position;i<data.length();i++){
		std::string let = data.substr(i, 1);
		if(let == what){
			return(i);
		}
	}
	return(-1);
}

int main(int argc, char** argv){
	ArguementHandler Args(argc, argv);

	std::string outputFile = "OneHeader_out.hpp";
	std::vector<std::string> inputFiles;

	if(Args.hasArg("-o")){
		outputFile = Args.findArgs("-o")[0].value;
	}
	if(Args.hasArg("")){
		auto inputs = Args.findArgs("");
		for(int i=0;i<inputs.size();i++){
			inputFiles.push_back(inputs[i].value);
		}
	}

	std::cout<<"outputFile:  "<<outputFile<<std::endl;
	std::cout<<"inputFiles:  "<<std::endl;
	for(int i=0;i<inputFiles.size();i++){
		std::cout<<inputFiles[i]<<std::endl;
	}

	std::vector<std::filesystem::path> doneFiles;//TODO make into paths so json.hpp and ../json.hpp will be treated as the same thing because it is the same thing called from different locations.
	std::vector<std::string> systemIncludes;
	std::string outString;

	std::filesystem::path basePath = std::filesystem::current_path();

	for(int i=0;i<inputFiles.size();i++){
		parse(&doneFiles, &systemIncludes, &outString, inputFiles[i], basePath);
	}

	std::cout<<"Done files:  "<<std::endl;
	for(int i=0;i<doneFiles.size();i++){
		std::cout<<doneFiles[i]<<std::endl;
	}

	std::cout<<"Found system includes:  "<<std::endl;
	for(int i=0;i<systemIncludes.size();i++){
		std::cout<<systemIncludes[i]<<std::endl;
	}
}

void parse(std::vector<std::filesystem::path>* doneFiles, std::vector<std::string>* systemIncludes, std::string* outString, std::filesystem::path inputFilename, std::filesystem::path currentPath){
	doneFiles->push_back(inputFilename);
	//std::string pathChange = currentPath.lexically_normal().string();
	//if(pathChange.substr(pathChange.length()-2, 1) != "/"){
	//	pathChange.append("/");
	//}
	std::string fileContents = readFile(inputFilename.string());
	if(fileContents == ""){
		std::cout<<"Unable to find file '"<<inputFilename<<"'"<<std::endl;
		return;
	}
	std::vector<size_t> includeIndexes;
	findAllOccurances(includeIndexes, fileContents, "#include ");

	for(int i=0;i<includeIndexes.size();i++){
		includeIndexes[i] += 9;//length of the include statement
	}
	
	int maxIncludeLength = 35;

	for(int i=0;i<includeIndexes.size();i++){
		auto nextChar = findNextChar(fileContents, includeIndexes[i]);
		std::string let = nextChar.first;
		int let_pos = nextChar.second;
		//std::cout<<"nextchar "<<let<<std::endl;
		if(let == "\""){
			int nextIndex = findNextOccurenceChar(fileContents, let_pos+1, "\"");
			std::string includeContents = fileContents.substr(let_pos+1, nextIndex-(let_pos+1));
			if(includeContents.length() > maxIncludeLength){
				continue;
			}
			//std::cout<<"Found local include:  "<<includeContents<<std::endl;
			
			std::filesystem::path itemPath = (currentPath/std::filesystem::path(includeContents)).lexically_normal();
			std::filesystem::path newPath = itemPath.parent_path();
			if(std::find(doneFiles->begin(), doneFiles->end(), itemPath) != doneFiles->end()) {
				std::cout<<"Found repeat include of '"<<itemPath.string()<<"'"<<std::endl;
			} else {
				parse(doneFiles, systemIncludes, outString, itemPath, newPath);//yay recursion.  what could go wrong?
			}
		}else if(let == "<"){
			int nextIndex = findNextOccurenceChar(fileContents, let_pos+1, ">");
			std::string includeContents = fileContents.substr(let_pos+1, nextIndex-(let_pos+1));
			if(includeContents.length() > maxIncludeLength){
				continue;
			}
			//std::cout<<"Found system include:  "<<includeContents<<std::endl;
			if(std::find(systemIncludes->begin(), systemIncludes->end(), includeContents) != systemIncludes->end()) {
				//done't announce it to the whole world.  this one is just gonna happen :/
			} else {
				systemIncludes->push_back(includeContents);
			}
		}
	}
}

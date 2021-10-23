#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <filesystem>
#include "ArguementHandler/ArgHandle.hpp"
#include "SimpleCppTextFileHandler/file.hpp"

int main(int argc, char** argv){
	ArguementHandler Args(argc, argv);

	std::string outputFile = "Plugin_out.CP2DGP";
	std::string inputFolder = "";

	if(Args.hasArg("-o")){
		outputFile = Args.findArgs("-o")[0].value;
	}
	if(Args.hasArg("")){
		inputFolder = Args.findArgs("")[0].value;
	}

	if(inputFolder == "" || outputFile == ""){
		std::cout<<"didn't find both input and output folders(eg. they weren't both filled out)"<<std::endl;
		return(0);
	}

	std::cout<<"outputFile:  "<<outputFile<<std::endl;
	std::cout<<"inputFiles:  "<<std::endl;
	
	system(("zip -r "+ outputFile + " " + inputFolder).c_str());//WARNING NOT SAFE !!WARNING!!
	return(0);
}

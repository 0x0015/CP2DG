#include "RuntimeLoader.hpp"
#include "../CP2DG.hpp"
#include "CppGen.hpp"
#include "zip.hpp"
#include "../JsonLoader/JsonLoader.hpp"

RuntimeLoader::RuntimeLoader(CP2DG* mw){
	mainWindow = mw;
}

void RuntimeLoader::deleteCache(){
	if(fileExists(buildDir)){
		deleteFile(buildDir);
	}
}

bool RuntimeLoader::build(){
	if(mainWindow == NULL || buildDir == "" || sourceDir == ""){
		return(false);
	}
	
	if(!fileExists(sourceDir)){
		return(false);
	}
	if(!fileExists(buildDir)){
		createFolder(buildDir);
	}

	std::vector<std::string> paths;
	for(const auto & entry : std::filesystem::recursive_directory_iterator(sourceDir)){
		if(entry.path().extension() == ".CP2DGP"){
			paths.push_back(entry.path().string());
		}
	}

	if(mainWindow->debug){
		for(int i=0;i<paths.size();i++){
			std::cout<<"Found behavior:  " + paths[i]<<std::endl;
		}
	}
	
	std::vector<std::string> cppPaths;

	for(int i=0;i<paths.size();i++){
		std::shared_ptr<Zip> currentZipFile = std::make_shared<Zip>(paths[i]);
		if(currentZipFile->readable == false){
			continue;
		}
		std::vector<std::string> zipEntries = currentZipFile->listFiles();
		for(int x=0;x<zipEntries.size();x++){
			std::string newFilename = buildDir + "/" + zipEntries[x];
			currentZipFile->writeFileToDisk(zipEntries[x], newFilename);
			if(newFilename.substr(newFilename.length()-4, 4) == ".cpp"){
				cppPaths.push_back(newFilename);
			}
		}
	}
	
	using CppGenType = CppGen<std::pair<std::string, std::shared_ptr<JsonLoaderDef_Base>>, int>;//before thinking of using a using statement this was a nightmare

	CppGenType::compilerOptions = "-l:main.so";
	std::vector<std::shared_ptr<CppGenType>> CppGens;
	for(int i=0;i<cppPaths.size();i++){
		std::shared_ptr<CppGenType> tempGen = std::make_shared<CppGenType>(cppPaths[i], true, "g++", "getGameObject");//later add simultanious threaded building
		tempGen->generateCode();
		if(tempGen->generated == true && tempGen->error == false){
			auto call = tempGen->call(0);
			if(call){
				JsonLoader::JsonLoaderDefs[call.value().first] = call.value().second;
				if(mainWindow->debug){
					std::cout<<"Successfully built and added json loader for " + call.value().first<<std::endl;
				}
			}
			
		}else{
			std::cout<<"Error generating " + cppPaths[i] + ":\n";
			std::cout<<tempGen->compilerOutput<<std::endl;
		}
	}
	return(true);
}

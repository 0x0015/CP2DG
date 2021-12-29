#include "RuntimeLoader/RuntimeLoader.hpp"
#include "CP2DG.hpp"
#include <dlfcn.h>
#include <thread>
#include "../SimpleCppTextFileHandler/file.hpp"
#include "zip.hpp"
#include "JsonLoader/JsonLoader.hpp"

RuntimeLoader::RuntimeLoader(CP2DG* mw){
	mainWindow = mw;
}

void RuntimeLoader::deleteCache(){
	if(fileExists(buildDir)){
		deleteFile(buildDir);
	}
}

typedef std::pair<std::string, std::shared_ptr<JsonLoaderDef_Base>>(*CppFuncType)();



std::vector<std::string> splitString(std::string source, std::string delimiter){
	std::string s = source;
	std::vector<std::string> output;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    output.push_back(token);
	    s.erase(0, pos + delimiter.length());
	}
	output.push_back(s);
	return(output);
}

bool RuntimeLoader::build(){
	if(mainWindow == NULL || buildDir == "" || sourceDir == ""){
		return(false);
	}
	
	if(!fileExists(sourceDir)){
		createFolder(sourceDir);
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

	for(const auto & entry : std::filesystem::recursive_directory_iterator("Content/Plugins")){
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
	std::vector<std::string> funcNamesPaths;
	std::string startingLevelPath;

	for(int i=0;i<paths.size();i++){
		std::shared_ptr<Zip> currentZipFile = std::make_shared<Zip>(paths[i]);
		if(currentZipFile->readable == false){
			continue;
		}
		std::vector<std::string> zipEntries = currentZipFile->listFiles();
		for(int x=0;x<zipEntries.size();x++){
			std::string newFilename = buildDir + "/" + zipEntries[x];
			if(!fileExists(newFilename)){
				currentZipFile->writeFileToDisk(zipEntries[x], newFilename);
			}
			//std::cout<<currentZipFile->readFile(zipEntries[x]).value().first<<std::endl;
			if(newFilename.substr(newFilename.length()-4, 4) == ".cpp"){
				cppPaths.push_back(newFilename);
				std::cout<<"Found cpp file:  "<<newFilename<<std::endl;
			}
			if(newFilename.substr(newFilename.length() - 6, 6) == "Loader"){
				funcNamesPaths.push_back(newFilename);
				std::cout<<"Found Loader file:  "<<newFilename<<std::endl;
			}
			if(newFilename.substr(newFilename.length() - 4, 4) == "Init"){
				startingLevelPath = newFilename;
				std::cout<<"Found Init file:  "<<newFilename<<std::endl;
			}
		}
	}

	std::vector<std::string> funcNames;
	for(int i=0;i<funcNamesPaths.size();i++){
		std::string funcName = readFile(funcNamesPaths[i]);
		std::vector<std::string> splitLoaders = splitString(funcName, "\n");
		for(int i2=0;i2<splitLoaders.size();i2++){
			splitLoaders[i2].erase(remove(splitLoaders[i2].begin(), splitLoaders[i2].end(), ' '), splitLoaders[i2].end());
			splitLoaders[i2].erase(remove(splitLoaders[i2].begin(), splitLoaders[i2].end(), '\n'), splitLoaders[i2].end());
			splitLoaders[i2].erase(remove(splitLoaders[i2].begin(), splitLoaders[i2].end(), '\t'), splitLoaders[i2].end());
			//remove whitespace that could be mistakenly in there
			if(splitLoaders[i2] != ""){
				std::cout<<"found func to load:  "<<splitLoaders[i2]<<std::endl;
				funcNames.push_back(splitLoaders[i2]);
			}
		}
	}

	std::string startingLevel;
	{
		startingLevel = readFile(startingLevelPath);
		startingLevel.erase(remove(startingLevel.begin(), startingLevel.end(), ' '), startingLevel.end());
		startingLevel.erase(remove(startingLevel.begin(), startingLevel.end(), '\n'), startingLevel.end());
		startingLevel.erase(remove(startingLevel.begin(), startingLevel.end(), '\t'), startingLevel.end());
		if(startingLevel == ""){
			std::cout<<"Warning:  did not find starting level"<<std::endl;
		}else{
			mainWindow->loadInitialLevel = startingLevel;
		}
	}

	
	//using CppGenType = std::pair<std::string, std::shared_ptr<JsonLoaderDef_Base>>;//before thinking of using a using statement this was a nightmare

#if defined(_WIN32) || defined(_WIN64)
	std::string sharedObjectExtention = ".dll";
	std::string defaultOptions = "-fPIC -static -static-libgcc -static-libstdc++ -std=c++20 -Iinclude -IRuntime";
#else
	std::string sharedObjectExtention = ".so";
	std::string defaultOptions = "-fPIC -std=c++20 -Iinclude -IRuntime";
#endif

	std::string compiler = "g++";

	std::string linkerOptions = "-Wl,-rpath='${ORIGIN}/..' -export-dynamic main.so";
	std::string compilerOptions = "";
	std::string soName = "FuncGen";

	std::vector<std::string> objPaths;

	createFolder(buildDir);

	for(int i=0;i<cppPaths.size();i++){//make this one parralel
		std::string code = readFile(cppPaths[i]);
		if(code == ""){
			errors.push_back("Unable to open file: " + cppPaths[i]);
			continue;
		}
		std::size_t codeHash = std::hash<std::string>{}(code);
		std::string hash = std::to_string(codeHash);
		
		if(fileExists(buildDir + "/" + hash + ".o")){
			objPaths.push_back(buildDir + "/" + hash + ".o");
			continue;
		}
		
		std::string command = compiler + " " +  defaultOptions + " " + cppPaths[i] + " " + compilerOptions + " -c -g -o " + buildDir + "/" + hash + ".o "  + " 2>&1";
				
		std::cout<<"Running Command: "<<command<<std::endl;
		char buffer[128];
		FILE* pipe = popen(command.c_str(), "r");
		if(!pipe){
			//error = true;
			//generated = false;
			continue;
		}
		std::string NextcompilerOutput = "";
		while(!feof(pipe)){
			if(fgets(buffer, 128, pipe) != NULL){
				NextcompilerOutput += buffer;
			}
		}
		pclose(pipe);
		errors.push_back(NextcompilerOutput);
		objPaths.push_back(buildDir + "/" + hash + ".o");
	}


	std::string compileObjs = "";
	
	for(int i=0;i<objPaths.size();i++){
		compileObjs.append(objPaths[i] + " ");
	}
	
	std::string link_command = compiler + " -shared -g -o " + buildDir + "/" + soName + sharedObjectExtention + " " + compileObjs + " " + linkerOptions + " 2>&1";
		
	std::cout<<"Running Command: "<<link_command<<std::endl;
	char buffer[128];
	FILE* pipe = popen(link_command.c_str(), "r");
	if(!pipe){
		//error = true;
		//generated = false;
		//continue;
	}
	std::string NextcompilerOutput = "";
	while(!feof(pipe)){
		if(fgets(buffer, 128, pipe) != NULL){
			NextcompilerOutput += buffer;
		}
	}
	pclose(pipe);
	errors.push_back(NextcompilerOutput);
	
		
	char *derror;
	std::cout<<"dlopen "<<buildDir + "/" + soName + sharedObjectExtention<<std::endl;
	void* dllHandle = dlopen ((buildDir + "/" + soName + sharedObjectExtention).c_str(), RTLD_NOW);
	if (!dllHandle) {
		//fputs (dlerror(), stderr);
		std::cout<<"Encountered a dlopen error"<<std::endl;
		errors.push_back(std::string(dlerror()));
		//error = true;
		//generated = false;
		for(int i=0;i<errors.size();i++){
			std::cout<<errors[i]<<std::endl;
		}
		return(false);
	}
	// get the function address and make it ready for use


	for(int i=0;i<funcNames.size();i++){
		std::cout<<"dlsym "<<dllHandle<<", "<<funcNames[i]<<std::endl;
		void* func = dlsym(dllHandle, funcNames[i].c_str());
		if (func == NULL)  {
			//fputs(derror, stderr);
			//exit(1);
			std::cout<<"encountered dlsym error"<<std::endl;
			errors.push_back(std::string(dlerror()));
			//error = true;
			//generated = false;
			continue;
		}
		std::cout<<"calling dlsymed function "<<funcNames[i]<<std::endl;
		auto call = ((CppFuncType)func)();
		JsonLoader::JsonLoaderDefs[call.first] = call.second;
		
	}

	dlclose(dllHandle);
	for(int i=0;i<errors.size();i++){
		if(errors[i] == "" || errors[i] == " "){
			errors.erase(errors.begin() + i);
			i-=1;
		}
	}
	for(int i=0;i<errors.size();i++){
		std::cout<<errors[i]<<std::endl;
	}

	
	return(true);
}

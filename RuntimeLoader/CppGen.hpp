#pragma once
#include <iostream>
#include <functional>
#include <thread>
#include <dlfcn.h>
#include "../SimpleCppTextFileHandler/file.hpp"
#include <optional>


template<typename T, typename T2> class CppGen{
public:
	bool waitForCodeGen = true;
	std::thread codeGenThread;
	bool generated = false;
	bool error = false;
	std::string path;
	
#if defined(_WIN32) || defined(_WIN64)
	std::string sharedObjectExtention = ".dll";
	std::string defaultOptions = "-fPIC -static -static-libgcc -static-libstdc++ -std=c++20 -Wl,-rpath='${ORIGIN}/..'";
#else
	std::string sharedObjectExtention = ".so";
	std::string defaultOptions = "-fPIC -std=c++20 -Wl,-rpath='${ORIGIN}/..'";
#endif

	std::string functionName = "main";
	std::string compilerOutput = "";
	static inline std::string compiler = "g++";
	static inline std::string compileDirectory = "Runtime";
	static inline std::string compilerOptions = "";
	void* dllHandle;
	T (*func)(T2);
	T defaultValue;
	void generateCodeFunc(){
		
		//if(fileExists("DllTemp")){
		//	deleteFile("DllTemp");
		//}
		std::string dllTempFolder = compileDirectory;
		createFolder(dllTempFolder);
		std::string code = readFile(path);
		std::size_t codeHash = std::hash<std::string>{}(code);
		std::string hash = std::to_string(codeHash);
		//writeFile(dllTempFolder + "/" + hash + ".cpp", *code);
		
		bool compiledFileExists = false;
		
		if(fileExists(dllTempFolder + "/" + hash + sharedObjectExtention)){
			compiledFileExists = true;
		}
		std::string command = compiler + " -shared -g -o " + dllTempFolder + "/" + hash + sharedObjectExtention + " " + defaultOptions + " " + path + " " + compilerOptions + " 2>&1";
		
		
		if(!compiledFileExists){
			std::cout<<"Running Command: "<<command<<std::endl;

			char buffer[128];
			FILE* pipe = popen(command.c_str(), "r");
			if(!pipe){
				error = true;
				generated = false;
				return;
			}
			compilerOutput = "";
			while(!feof(pipe)){
				if(fgets(buffer, 128, pipe) != NULL){
					compilerOutput += buffer;
				}
			}
			pclose(pipe);
		}
	
		char *derror;
		    dllHandle = dlopen ((dllTempFolder + "/"+ hash + sharedObjectExtention).c_str(), RTLD_LAZY);

		    if (!dllHandle) {
		        //fputs (dlerror(), stderr);
			compilerOutput += dlerror();
		        error = true;
			generated = false;
			return;
		    }
		    // get the function address and make it ready for use
		    func = (T(*)(T2)) dlsym(dllHandle, functionName.c_str());
		    if ((derror = dlerror()) != NULL)  {
		        //fputs(derror, stderr);
		        //exit(1);
			compilerOutput += derror;
			error = true;
			generated = false;
			return;
		    }
		    //dlclose(handle);
		    
		error = false;
		generated = true;


	}
	void generateCode(){
		generated = false;
		error = false;
		if(codeGenThread.joinable()){
			codeGenThread.join();
		}
		codeGenThread = std::thread([this] {generateCodeFunc(); });
		if(waitForCodeGen){
			codeGenThread.join();
		}
	}
	void waitForCompilation(){
		codeGenThread.join();
	}
	void generateCode(bool wait, std::string comp = "g++", std::string funcName = "main"){
		waitForCodeGen = wait;
		compiler = comp;
		functionName = funcName;
		generateCode();
	}
	std::optional<T> call(T2 arg){
		if(generated && (!error)){
			return(func(arg));
		}
		return(std::nullopt);
	}
	std::function<T(T2)> getStdFunction(){
		if(generated && (!error)){
			return(std::function<T(T2)>(func));
		}
		return(std::function<T(T2)>());
	}
	CppGen(std::string c, bool wait = true, std::string comp = "g++", std::string funcName = "main"){
		path = c;
		waitForCodeGen = wait;
		compiler = comp;
		functionName = funcName;
	}
	~CppGen(){

	}
};

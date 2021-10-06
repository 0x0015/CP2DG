#include <iostream>
#include "CppGen.hpp"
#include "GameObjects/GameObject.hpp"

template<typename T, typename T2> void CppGen<T, T2>::generateCodeFunc(){
		
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

		//std::string compiler = "g++";
#if defined(_WIN32) || defined(_WIN64)
		if(fileExists(dllTempFolder + "/" + hash + ".dll")){
			compiledFileExists = true;
		}
		std::string command = compiler + " -shared -g -o " + dllTempFolder + "/" + hash + ".dll -fPIC -static -static-libgcc -static-libstdc++ " + path + " " + compilerOptions + " 2>&1";
		
#else
		if(fileExists(dllTempFolder + "/" + hash + ".so")){
			compiledFileExists = true;
		}
		std::string command = compiler + " -shared -g -o " + dllTempFolder + "/" + hash + ".so -fPIC " + path + " " + compilerOptions + " 2>&1";
		
#endif
		//system(command.c_str());
		if(!compiledFileExists){
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
		    //double_ptr GetDouble;
		    //if(dllHandle){
		    //	dlclose(dllHandle);
		    // }
		    // open the *.so
#if defined(_WIN32) || defined(_WIN64)
		    dllHandle = dlopen ((dllTempFolder + "/"+ hash + ".dll").c_str(), RTLD_LAZY);
#else
		    dllHandle = dlopen ((dllTempFolder + "/"+ hash + ".so").c_str(), RTLD_LAZY);
#endif
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
		    //// call the function in *.so
		    //printf ("%f\n", (*GetDouble)(2.0));
		    //// remember to free the resource
		    //dlclose(handle);
		    
		error = false;
		generated = true;
	}
template<typename T, typename T2> void CppGen<T, T2>::generateCode(){
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
template<typename T, typename T2> void CppGen<T, T2>::generateCode(bool wait, std::string comp, std::string funcName){
		waitForCodeGen = wait;
		compiler = comp;
		functionName = funcName;
		generateCode();
	}
template<typename T, typename T2> T CppGen<T, T2>::call(T2 arg){
		if(generated && (!error)){
			return(func(arg));
		}
		return(defaultValue);
	}
template<typename T, typename T2> std::function<T(T2)> CppGen<T, T2>::getStdFunction(){
		if(generated && (!error)){
			return(std::function<T(T2)>(func));
		}
		return(std::function<T(T2)>());
	}
template<typename T, typename T2> CppGen<T, T2>::CppGen(std::string c, bool wait, std::string comp, std::string funcName){
		//s = tcc_new();
		path = c;
		waitForCodeGen = wait;
		compiler = comp;
		functionName = funcName;
	}
template<typename T, typename T2> CppGen<T, T2>::~CppGen(){
		//tcc_delete(s);
	}

template class CppGen<float, int>;
//template class CppGen<void, void>;
template class CppGen<GameObject*, int>;

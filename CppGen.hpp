#pragma once
#include <iostream>
#include <functional>
#include <thread>
#include <dlfcn.h>
//#include "getDllPath.hpp"
#include "SimpleCppTextFileHandler/file.hpp"
//#include <libtcc.h>
//#include "getDllPath.hpp"
//#include <template>
template<typename T, typename T2> class CppGen{
public:
	bool waitForCodeGen = true;
	std::thread codeGenThread;
	bool generated = false;
	bool error = false;
	std::string path;
	//TCCState* s = 0;
	std::string functionName = "main";
	std::string compilerOutput = "";
	static inline std::string compiler = "g++";
	static inline std::string compileDirectory = "DllTemp";
	static inline std::string compilerOptions = "";
	void* dllHandle;
	T (*func)(T2);
	T defaultValue;
	void generateCodeFunc();
	void generateCode();
	void generateCode(bool wait, std::string comp = "g++", std::string funcName = "main");
	T call(T2 arg);
	std::function<T(T2)> getStdFunction();
	CppGen(std::string c, bool wait = true, std::string comp = "g++", std::string funcName = "main");
	~CppGen();
};

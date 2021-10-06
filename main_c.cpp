//#define SDL_MAIN_HANDLED
#include "Main.hpp"
#include "ArguementHandler/ArgHandle.hpp"
#include "SDL2/SDL_gpu.h"
#include <stdexcept>
#include <memory>

int ErrorCallback(GPU_LogLevelEnum log_level, const char* format, va_list args){
	std::cout<<"GPU Error format:  "<<format<<std::endl;
	std::cout<<"GPU Error args:  "<<args<<std::endl;
	vprintf(format, args);
	throw std::runtime_error("Gpu Error");
}

int main(int argc, char** argv){
	//SDL_SetMainReady();
	GPU_SetLogCallback(ErrorCallback);
	ArguementHandler* args = new ArguementHandler(argc, argv);
	std::shared_ptr<Main> mainClass = std::make_shared<Main>(args);
	mainClass->Initialize();
	mainClass->Load();
	while(mainClass->running == 1){
		mainClass->Update();
	}
	int run = mainClass->running;
	return(run);
}



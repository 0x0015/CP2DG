#include "AssetLoader.hpp"
#include <SDL2/SDL_gpu.h>
#define FC_USE_SDL_GPU
#define NFONT_USE_SDL_GPU
#include "NFont/NFont_gpu.h"
#include "Shader.hpp"
#include "ComputeShader.hpp"
#include "audio.h"

void AssetLoader::ImageRequiredPath(std::string path, std::string name){
	std::string n = name;
	if(n == ""){
		n = path;
	}
	if(!Images.contains(n)){
		Images[n] = 0;
	}
}
void AssetLoader::AudioRequiredPath(std::string path, std::string name){
	std::string n = name;
	if(n == ""){
		n = path;
	}
	if(!Audios.contains(n)){
		Audios[n] = 0;
	}
}
void AssetLoader::FontRequiredPath(std::string path, int size, std::string name){
	std::string n = name;
	if(n == ""){
		n = path;
	}
	if(!Fonts.contains(std::pair<std::string, int>(n, size))){
		Fonts[std::pair<std::string, int>(n, size)] = 0;
	}
}
void AssetLoader::ShaderRequiredPath(std::string fpath, std::string vpath){
	if(!Shaders.contains(std::pair<std::string, std::string>(fpath, vpath))){
		Shaders[std::pair<std::string, std::string>(fpath, vpath)] = 0;
	}
}

void AssetLoader::ComputeShaderRequiredPath(std::string path, std::string name){
	std::string n = name;
	if(n == ""){
		n = path;
	}
	if(!ComputeShaders.contains(n)){
		ComputeShaders[n] = 0;
	}
}

void AssetLoader::LoadImages(){
	for(auto it : Images){
		if(it.second == 0){
			Images[it.first] = GPU_LoadImage((contentFolder + "/Images/" + it.first).c_str());
			if(mainWindow->debug)
				std::cout<<"Loading Image:  "<<it.first<<" with "<<Images[it.first]<<std::endl;
		}
	}
}
void AssetLoader::LoadAudio(){
	for(auto it : Audios){
		if(it.second == 0){
			//SDLAudio* tempAudio = new SDLAudio();
			//SDL_LoadWAV((contentFolder + "/Audio/" + it.first).c_str(), &tempAudio->wav_spec, &tempAudio->wav_buffer, &tempAudio->wav_length);
			

			Audios[it.first] = createAudio((contentFolder + "/Audio/" + it.first).c_str(), 0, SDL_MIX_MAXVOLUME);
			if(mainWindow->debug)
				std::cout<<"Loading Audio:  "<<it.first<<" with "<<Audios[it.first]<<std::endl;
		}
	}
}
void AssetLoader::LoadFonts(){
	for(auto it : Fonts){
		if(it.second == 0){
			Fonts[it.first] = new NFont((contentFolder + "/Fonts/" + it.first.first).c_str(), it.first.second);
			if(mainWindow->debug)
				std::cout<<"Loading Font:   "<<it.first.first<<" size "<<it.first.second<<" with "<<Fonts[it.first]<<std::endl;
		}
	}
}

void AssetLoader::LoadShaders(){
	for(auto it : Shaders){
		if(it.second == 0){
			std::string shaderID;
			std::string Vert;
			if(it.first.second == ""){
				shaderID = it.first.first;
				Vert = "v1.vert";
			}else{
				shaderID = it.first.first + "_" + it.first.second;
				Vert = it.first.second;
			}
			Shaders[it.first] = new Shader(shaderID, contentFolder + "/Shaders/" + Vert, contentFolder + "/Shaders/" + it.first.first);
			if(mainWindow->debug)
				std::cout<<"Loading Shader  frag:"<<it.first.first<<" vert:"<<it.first.second<<" with "<<Shaders[it.first]<<std::endl;
		}
	}
}
void AssetLoader::LoadComputeShaders(){
	for(auto it : ComputeShaders){
		if(it.second == 0){
			ComputeShaders[it.first] = new ComputeShader(contentFolder + "/Shaders/" + it.first);
			if(mainWindow->debug)
				std::cout<<"Loading Compute shader:   "<<it.first<<" with "<<ComputeShaders[it.first]<<std::endl;
		}
	}
}
void AssetLoader::ImageUnload(std::string name){
	if(!Images.contains(name)){
		return;
	}
	GPU_FreeImage(Images[name]);
	Images.erase(name);
}

void AssetLoader::AudioUnload(std::string name){
	if(!Audios.contains(name)){
		return;
	}
	freeAudio(Audios[name]);
	//delete(Audios[name]);
	Audios.erase(name);
}

void AssetLoader::FontUnload(std::pair<std::string, int> name){
	if(!Fonts.contains(name)){
		return;
	}
	delete(Fonts[name]);
	Fonts.erase(name);
}
void AssetLoader::ShaderUnload(std::pair<std::string, std::string> name){
	if(!Shaders.contains(name)){
		return;
	}
	delete(Shaders[name]);
	Shaders.erase(name);
}
void AssetLoader::ComputeShaderUnload(std::string name){
	if(!ComputeShaders.contains(name)){
		return;
	}
	delete(ComputeShaders[name]);
	ComputeShaders.erase(name);
}
void AssetLoader::ImageUnloadAll(){
	for(auto it : Images){
		GPU_FreeImage(it.second);
	}
	Images.clear();
}

void AssetLoader::AudioUnloadAll(){
	pauseAudio();
	for(auto it : Audios){
		freeAudio(it.second);
		//delete(it.second);
	}
	Audios.clear();
}

void AssetLoader::FontUnloadAll(){
	for(auto it : Fonts){
		delete(it.second);
	}
	Fonts.clear();
}
void AssetLoader::ShaderUnloadAll(){
	for(auto it : Shaders){
		delete(it.second);
	}
	Shaders.clear();
}
void AssetLoader::ComputeShaderUnloadAll(){
	for(auto it : ComputeShaders){
		delete(it.second);
	}
	ComputeShaders.clear();
}
AssetLoader::~AssetLoader(){
	ImageUnloadAll();
	AudioUnloadAll();
	FontUnloadAll();
	ShaderUnloadAll();
}

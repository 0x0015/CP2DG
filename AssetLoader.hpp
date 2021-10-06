#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
#include <unordered_map>
#include <utility>
#include "audio.h"
#include "Main.hpp"

struct pair_hash //https://www.techiedelight.com/use-std-pair-key-std-unordered_map-cpp/
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class NFont;
class Shader;
class ComputeShader;
class CP2DG;

class AssetLoader{
public:
	CP2DG* mainWindow;

	std::string contentFolder = "Content";
	std::unordered_map<std::string, GPU_Image*> Images;
	std::unordered_map<std::string, Audio*> Audios;
	std::unordered_map<std::pair<std::string, int>, NFont*, pair_hash> Fonts;
	std::unordered_map<std::pair<std::string, std::string>, Shader*, pair_hash> Shaders;
	std::unordered_map<std::string, ComputeShader*> ComputeShaders;

	void ImageRequiredPath(std::string path, std::string name = "");
	void AudioRequiredPath(std::string path, std::string name = "");
	void FontRequiredPath(std::string path, int size, std::string name = "");
	void ShaderRequiredPath(std::string fpath, std::string vpath = "");
	void ComputeShaderRequiredPath(std::string path, std::string name = "");

	void ImageUnload(std::string name);
	void AudioUnload(std::string name);
	void FontUnload(std::pair<std::string, int> name);
	void ShaderUnload(std::pair<std::string, std::string> name);
	void ComputeShaderUnload(std::string name);

	void ImageUnloadAll();
	void AudioUnloadAll();
	void FontUnloadAll();
	void ShaderUnloadAll();
	void ComputeShaderUnloadAll();

	void LoadImages();
	void LoadAudio();
	void LoadFonts();
	void LoadShaders();
	void LoadComputeShaders();

	~AssetLoader();
};

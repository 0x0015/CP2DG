#pragma once
#include <string.h>
#include <algorithm>
#include <vector>
#include <SDL2/SDL_gpu.h>
#include <iostream>

class Shader {
public:
	Shader(const std::string& id, const std::string& v_str, const std::string& f_str) : id(id), img(NULL) {
		v = GPU_LoadShader(GPU_VERTEX_SHADER, v_str.c_str());
		bool shaderError = false;
		if (!v){
			std::cout << "Failed to load vertex shader: " << GPU_GetShaderMessage() << "\n";
			shaderError = true;
		}

		f = GPU_LoadShader(GPU_FRAGMENT_SHADER, f_str.c_str());

		if (!f){
			std::cout << "Failed to load fragment shader: " << GPU_GetShaderMessage() << "\n";
			shaderError = true;
		}

		p = GPU_LinkShaders(v, f);

		if (!p) {
			std::cout << "Failed to link shader program: " << GPU_GetShaderMessage() << "\n";
			shaderError = true;
		}
		if(!shaderError){
			//std::cout<<"Successfuly loaded and linked shader program"<<"\n";
		}
		block = GPU_LoadShaderBlock(p, "gpu_Vertex", "gpu_TexCoord", NULL, "gpu_ModelViewProjectionMatrix");
	}

	void freeImg() {
		if(img){
			GPU_FreeImage(img);
		}
	}
	~Shader() {
		freeImg();
	}

	void addImg(std::string path) {
		img = GPU_LoadImage(path.c_str());

		GPU_SetSnapMode(img, GPU_SNAP_NONE);
		GPU_SetWrapMode(img, GPU_WRAP_REPEAT, GPU_WRAP_REPEAT);
	}

	void addVariable(std::string idV) {
		Uint32 location = GPU_GetUniformLocation(p, idV.c_str());
		variables.push_back(std::make_pair(idV, location));
	}

	std::string getId() { return id; }

	void setImgShader() {
		GPU_SetShaderImage(img, getVar("tex1"), 1);
	}

	void activate() {
		GPU_ActivateShaderProgram(p, &block);
	}

	Uint32 getVar(std::string idV) {
		auto it = std::find_if(variables.begin(), variables.end(), [idV](std::pair<std::string, Uint32> p) { return p.first == idV; });

		if (it != variables.end())
			return it->second;

		return (Uint32)(-1);
	}

private:
	std::string id;
	Uint32 v, f, p;
	std::vector<std::pair<std::string, Uint32>> variables;
	GPU_ShaderBlock block;
	GPU_Image *img;
};

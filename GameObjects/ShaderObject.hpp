#pragma once
#include "Sprite.hpp"
#include <unordered_map>
#include <vector>

class Shader;

class ShaderObject : public Sprite{
public:
	std::string vert = "";
	std::string frag = "";
	Shader* shad;
	std::unordered_map<std::string, int> UniformI;
	std::unordered_map<std::string, unsigned int> UniformUI;
	std::unordered_map<std::string, float> UniformF;
	std::unordered_map<std::string, std::vector<int>> UniformIV;
	std::unordered_map<std::string, std::vector<unsigned int>> UniformUIV;
	std::unordered_map<std::string, std::vector<float>> UniformFV;
	std::vector<std::string> additionalVariables;
	std::vector<std::string> Images;
	std::pair<int, int> renderResolution;
	GPU_Image* blankTexture;
	void Draw();
	void Update();
	void Load();
	void Initialize();
	~ShaderObject();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "std::pair<float,float>"},
		{"SpawnTime", "int"},
		{"depth", "float"},
		{"name", "std::string"},
		{"size", "std::pair<float,float>"},
		{"rotation", "float"},
		{"center", "std::pair<float,float>"},
		{"vert", "std::string"},
		{"frag", "std::string"},
		{"renderResolution", "std::pair<int,int>"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name},
		{"size", &size},
		{"rotation", &rotation},
		{"center", &center},
		{"vert", &vert},
		{"frag", &frag},
		{"renderResolution", &renderResolution}
	};

};

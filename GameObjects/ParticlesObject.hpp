#pragma once
#include "GameObject.hpp"
#include <vector>

class ComputeShader;

struct ParticlePos{
	float x, y, r, g, b, a;
};

struct ParticleData{
	float time;
	uint32_t behavior;//shader uint is a 32 bit unsigned int
};

class ParticlesObject : public GameObject{
public:
	std::vector<ParticlePos> startingParticlePoses;
	std::vector<ParticleData> startingParticleDatas;
	ComputeShader* shader;
	void Initialize();
	void Load();
	void Update();
	void Draw();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "std::pair<float,float>"},
		{"SpawnTime", "int"},
		{"depth", "float"},
		{"name", "std::string"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name}
	};

};

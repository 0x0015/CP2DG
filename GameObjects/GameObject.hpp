#pragma once
#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
#include <memory>

class RenderObject;
class CP2DG;

class GameObject{
public:
	CP2DG* mainWindow;
	RenderObject* renderWindow;
	std::pair<float, float> position;
	int SpawnTime = 0;
	float depth;
	std::string name = "";
	bool toDelete = false;
	void moveAtAngle(float angle, float units);
	virtual void Initialize();
	virtual void Load();
	virtual void Draw();
	virtual void Update();
	virtual void Spawn();
	virtual ~GameObject();
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

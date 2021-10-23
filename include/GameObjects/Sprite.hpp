#pragma once
#include "GameObject.hpp"
#include <memory>

class Sprite : public virtual GameObject{
public:
	std::pair<float, float> size;
	float rotation;
	std::pair<float, float> center;
	//SDL_Surface* ImageSurface = 0;
	//SDL_Texture* Texture = 0;
	GPU_Image* Image;
	GPU_Target* ImageTarget;
	std::string ImagePath = "";
	void Initialize();
	void Load();
	void Draw();
	void Update();
	void PointToward(std::shared_ptr<GameObject> other);
	~Sprite();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "std::pair<float,float>"},
		{"SpawnTime", "int"},
		{"depth", "float"},
		{"name", "std::string"},
		{"size", "std::pair<float,float>"},
		{"rotation", "float"},
		{"center", "std::pair<float,float>"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name},
		{"size", &size},
		{"rotation", &rotation},
		{"center", &center}
	};
};

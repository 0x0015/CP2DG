#include "GameObject.hpp"

class NFont;

class TextObject : public GameObject{
public:
	NFont* font;
	std::string fontPath;
	SDL_Color drawColor = {0, 0, 0, 255};
	std::string text;
	std::pair<float, float> size = std::pair<float, float>(0, 0);
	int defaultTextSize = 20;
	float scale = 1;
	void Initialize();
	void Load();
	void Update();
	void Draw();
	~TextObject();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "std::pair<float,float>"},
		{"SpawnTime", "int"},
		{"depth", "float"},
		{"name", "std::string"},
		{"fontPath", "std::string"},
		{"drawColor", "SDL_Color"},
		{"text", "std::string"},
		{"size", "std::pair<float,float>"},
		{"defaultTextSize", "int"},
		{"scale", "float"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name},
		{"fontPath", &fontPath},
		{"drawColor", &drawColor},
		{"text", &text},
		{"size", &size},
		{"defaultTextSize", &defaultTextSize},
		{"scale", &scale}
	};

};

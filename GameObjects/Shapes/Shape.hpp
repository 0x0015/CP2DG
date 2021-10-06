#include "../GameObject.hpp"

class Shape : public GameObject{
public:
	SDL_Color fillColor;
	bool filled = false;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Shape();
};

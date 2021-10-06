#include "Shape.hpp"

class Ellipse : public Shape{
	float radius = 0;
	std::pair<float, float> size = std::pair<float, float>(0, 0);
	float rotation;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Ellipse();
};

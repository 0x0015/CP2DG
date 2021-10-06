#include "Shape.hpp"
#include <vector>

class Polygon : public Shape{
	std::vector<std::pair<float, float>> vertices;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Polygon();
};

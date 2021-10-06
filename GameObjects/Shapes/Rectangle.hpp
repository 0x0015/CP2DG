#include "Shape.hpp"

class RectangleShape : public Shape{
public:
	bool rounded = false;
	float radius = 0;
	std::pair<float, float> size;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~RectangleShape();
};

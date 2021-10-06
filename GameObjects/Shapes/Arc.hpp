#include "Shape.hpp"

class Arc : public Shape{
	float radius = 0;
	float startAngle;
	float endAngle;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Arc();
};

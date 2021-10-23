#pragma once
//#include "GameObjectV.hpp"
#include "../Sprite.hpp"
#include <vector>
#include <memory>

class RenderObject;

class Collidable : public virtual Sprite{
public:
	std::vector<std::pair<float, float>> CollisionPoints;
	void getCollisionPointsFromJsonText(std::string text);
	void getCollisionPointsFromJsonFile(std::string filename);
	bool CheckCollisions(std::shared_ptr<RenderObject> obj);
	void Draw();
};

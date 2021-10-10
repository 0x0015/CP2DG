#pragma once
#include "../CP2DG.hpp"

class testClass : public GameObject{
	void Initialize();
	void Load();
	void Update();
	void Draw();
	testClass();
	~testClass();
};

extern "C" std::pair<std::string, std::shared_ptr<JsonLoaderDef_Base>> getGameObject(int i);

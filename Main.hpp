#pragma once
#include "CP2DG.hpp"

class Main: public CP2DG{
public:
	void Initialize();
	void Load();
	void Update();
	void Draw();
	Main(ArguementHandler* a);
};

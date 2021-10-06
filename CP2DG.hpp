#pragma once
#include "flextGL.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
//#include "gl_core_3_0.h"
#include <vector>
#include "GameObjects/RenderObject.hpp"


//class GameObject;
class InputHandler;
class AssetLoader;
class ArguementHandler;

class CP2DG: public RenderObject{
public:
	bool debug = false;
	int ticks = 0;
	int running = 1;
	ArguementHandler* args = 0;
	SDL_Event event;
	//SDL_Window* window = 0;
	//SDL_Renderer* renderer = 0;
	//std::pair<int, int> mousePos;
	//std::pair<bool, bool> mouseState;
	std::string initialWindowTitle = "Hello CP2DG!";
	std::string loadInitialLevel = "";
	InputHandler* Input;
	AssetLoader* Assets;
	GameObject* player = 0;
	std::pair<int, int> resolution = std::pair<int, int>(0,0);
	std::pair<int, int> renderSize = std::pair<int, int>(0,0);
	//const Uint8* keyboardState = 0;
	void Initialize();
	void Load();
	void Update();
	void Draw();
	void CP2DGCreate(ArguementHandler* a = 0);
	CP2DG(ArguementHandler* a);
	CP2DG();
	~CP2DG();
};

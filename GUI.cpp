#include "GUI.hpp"
#include "Main.hpp"
#include <SDL2/SDL_gpu.h>
#include "GameObjects/TextObject.hpp"
#include "GameObjects/Shapes/Rectangle.hpp"

void GUI::Initialize(){
	depth = 5.0;
	name = "GUI";
	renderSize = std::pair<int, int>(1920, 1080);
	size = std::pair<int, int>(mainWindow->resolution.first, mainWindow->resolution.second);
	
	std::shared_ptr<TextObject> text = std::make_shared<TextObject>();
	text->position = std::pair<float, float>(100, 100);
	text->fontPath = "font.ttf";
	text->text = "testing";
	text->defaultTextSize = 40;
	GameObjects.push_back(text);

	RenderObject::Initialize();
	initialized = true;
	
}

void GUI::Load(){
	//font->load("Content/font.ttf", 40, NFont::Color(0,0,0));
	
	RenderObject::Load();
	loaded = true;
}

void GUI::addElement(std::shared_ptr<GameObject> obj){
	obj->mainWindow = mainWindow;
	obj->renderWindow = this;
	if(initialized){
		obj->Initialize();
	}
	if(loaded){
		obj->Load();
	}
	GameObjects.push_back(obj);
}

void GUI::Draw(){
	GPU_SetActiveTarget(Image->target);
	GPU_Clear(Image->target);
	for(int i=0;i<GameObjects.size();i++){
		GameObjects[i]->Draw();
	}

	//font->draw(window, 100, 100, "testing");

	GPU_SetActiveTarget(renderWindow->window);
	GPU_Rect DestR;
	DestR.x = position.first;
	DestR.y = position.second;
	DestR.w = size.first;
	DestR.h = size.second;
	SDL_Point RotP;
	RotP.x = center.first;
	RotP.y = center.second;
	//SDL_RenderCopyEx(mainWindow->renderer, Texture, NULL, &DestR, (double)rotation, &RotP, SDL_FLIP_NONE);
	
	//GPU_Translate(0, 0, depth);
	GPU_SetBlending(Image, true);
	GPU_SetBlendMode(Image, GPU_BLEND_NORMAL);
	//GPU_SetBlendFunction(Image, GPU_FUNC_SRC_ALPHA, GPU_FUNC_ONE_MINUS_SRC_ALPHA, GPU_FUNC_ONE, GPU_FUNC_ZERO );
	//GPU_SetRGBA(Image, 255, 100, 255, 127.5f + 127.5f*sin(SDL_GetTicks() / 1000.0f) * depth);
	GPU_BlitRectX(Image, NULL, renderWindow->window, &DestR, rotation, center.first, center.second, GPU_FLIP_NONE);
	GPU_Flip(Image->target);
	
}

void GUI::Update(){
	RenderObject::Update();
}

GUI::~GUI(){

}

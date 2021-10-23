#include "GameObjects/TextObject.hpp"
#include "Main.hpp"
#include <SDL2/SDL_gpu.h>
#define FC_USE_SDL_GPU
#define NFONT_USE_SDL_GPU
#include "../NFont/NFont_gpu.h"
#include "AssetLoader.hpp"

void TextObject::Initialize(){
	mainWindow->Assets->FontRequiredPath(fontPath, defaultTextSize);
}

void TextObject::Load(){
	font = mainWindow->Assets->Fonts[std::pair<std::string, int>(fontPath, defaultTextSize)];
}

void TextObject::Update(){
	font->setDefaultColor(drawColor);
}

void TextObject::Draw(){
	if(size == std::pair<float, float>(0, 0)){
		font->draw(renderWindow->window, position.first, position.second, scale, text.c_str());
	}else{
		GPU_Rect DestR;
		DestR.x = position.first;
		DestR.y = position.second;
		DestR.w = size.first;
		DestR.h = size.second;
		font->drawBox(renderWindow->window, DestR,scale, text.c_str());
	}
}

TextObject::~TextObject(){

}

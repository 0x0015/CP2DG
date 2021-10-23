#include "GameObjects/Shapes/Rectangle.hpp"
#include "GameObjects/RenderObject.hpp"
#include "Main.hpp"
void RectangleShape::Initialize(){

}

void RectangleShape::Load(){

}

void RectangleShape::Draw(){
	GPU_Rect DestR;
	DestR.x = position.first;
	DestR.y = position.second;
	DestR.w = size.first;
	DestR.h = size.second;

	if(!filled){
		if(rounded){
			GPU_RectangleRound2(renderWindow->window, DestR, radius, fillColor);
		}else{
			GPU_Rectangle2(renderWindow->window, DestR, fillColor);
		}
	}else{
		if(rounded){
			GPU_RectangleRoundFilled2(renderWindow->window, DestR, radius, fillColor);
		}else{
			GPU_RectangleFilled2(renderWindow->window, DestR, fillColor);
		}
	}
}

void RectangleShape::Update(){

}

RectangleShape::~RectangleShape(){

}

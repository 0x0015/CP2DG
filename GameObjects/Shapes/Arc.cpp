#include "Arc.hpp"
#include "../RenderObject.hpp"
#include "../../Main.hpp"
void Arc::Initialize(){

}

void Arc::Load(){

}

void Arc::Draw(){
	if(filled){
		GPU_Arc(renderWindow->window, position.first, position.second, radius, startAngle, endAngle, fillColor);
	}else{
		GPU_ArcFilled(renderWindow->window, position.first, position.second, radius, startAngle, endAngle, fillColor);
	}
}

void Arc::Update(){

}

Arc::~Arc(){

}

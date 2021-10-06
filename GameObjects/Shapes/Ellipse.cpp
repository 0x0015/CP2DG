#include "Ellipse.hpp"
#include "../RenderObject.hpp"
#include "../../Main.hpp"
void Ellipse::Initialize(){

}

void Ellipse::Load(){

}

void Ellipse::Draw(){
	std::pair<float, float> rad;
	if(size == std::pair<float, float>(0, 0)){
		rad = std::pair<float, float>(radius, radius);
	}else{
		rad = size;
	}

	if(filled){
		GPU_EllipseFilled(renderWindow->window, position.first, position.second, rad.first, rad.second, rotation, fillColor);

	}else{
		GPU_Ellipse(renderWindow->window, position.first, position.second, rad.first, rad.second, rotation, fillColor);
	}
}

void Ellipse::Update(){

}

Ellipse::~Ellipse(){

}

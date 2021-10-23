#include "GameObjects/Shapes/Polygon.hpp"
#include "GameObjects/RenderObject.hpp"
#include "Main.hpp"

void Polygon::Initialize(){

}

void Polygon::Load(){

}

void Polygon::Draw(){
	std::vector<float> verts;
	for(int i=0;i<vertices.size();i++){
		verts.push_back((position.first + vertices[i].first));
		verts.push_back((position.second + vertices[i].second));
	}
	float* float_verts = &verts[0];
	if(filled){
		GPU_Polygon(renderWindow->window, vertices.size(), float_verts, fillColor);
	}else{
		GPU_PolygonFilled(renderWindow->window, vertices.size(), float_verts, fillColor);

	}
}

void Polygon::Update(){

}

Polygon::~Polygon()
{

}

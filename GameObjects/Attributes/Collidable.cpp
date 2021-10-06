#include "Collidable.hpp"
#include "../RenderObject.hpp"
#include "../../JsonLoader/json.hpp"
#include "../../SimpleCppTextFileHandler/file.hpp"

using json = nlohmann::json;

bool Collidable::CheckCollisions(std::shared_ptr<RenderObject> canv){
	for(int i=0;i<CollisionPoints.size();i++){
		std::pair<int, int> point = std::pair<int, int>((CollisionPoints[i].first * size.first) + position.first, (CollisionPoints[i].second * size.second) + position.second);
		//std::cout<<"checking collisions, position"<<point.first<<", "<<point.second<<std::endl;
		if(canv->GetPixelColor(point).a != 0){
			return(true);
		}

	}
	return(false);
}

void Collidable::getCollisionPointsFromJsonText(std::string text){
	if(text == ""){
		std::cout<<"Json load error, text blank"<<std::endl;
		return;
	}
	auto j = json::parse(text);
	
	for(int i=0;i<j.size();i++){
		std::pair<float, float> point;
		if(j[i].size() == 2){
			point.first = j[i][0].get<float>();
			point.second = j[i][1].get<float>();
		}
		CollisionPoints.push_back(point);
	}

}

void Collidable::getCollisionPointsFromJsonFile(std::string filename){
	getCollisionPointsFromJsonText(readFile(filename));
}

void Collidable::Draw(){
	for(int i=0;i<CollisionPoints.size();i++){
		std::pair<int, int> point = std::pair<int, int>((CollisionPoints[i].first * size.first) + position.first, (CollisionPoints[i].second * size.second) + position.second);
		SDL_Color white = {255, 0, 0, 255};
		GPU_Pixel(renderWindow->window, point.first, point.second, white);
		//std::cout<<"checking collisions, position"<<point.first<<", "<<point.second<<std::endl;
		//if(canv->GetPixelColor(point).a != 0){
		//	return(true);
		//}

	}
}

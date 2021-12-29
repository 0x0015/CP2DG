#pragma once
#include "GameObject.hpp"
#include <vector>
#include <memory>

class RenderObject : public GameObject{
public:
	std::vector<std::shared_ptr<GameObject>> GameObjects;
	template<typename T> std::shared_ptr<T> FindObject(std::string name = ""){	
		if(name == ""){
			for(int i=0;i<GameObjects.size();i++){
				T* GOi = dynamic_cast<T*>(GameObjects[i].get());
				//std::cout<<"Dynamically casting"<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					return(std::dynamic_pointer_cast<T>(GameObjects[i]));
				}
			}
		}else{
			for(int i=0;i<GameObjects.size();i++){
				T* GOi = dynamic_cast<T*>(GameObjects[i].get());
				//std::cout<<"Dynamically casting name "<<name<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					if(GameObjects[i]->name == name){
						return(std::dynamic_pointer_cast<T>(GameObjects[i]));
					}
				}
			}
		}
		return(0);
	}
	template<typename T> std::shared_ptr<T> FindObjectRecursive(std::string name = ""){
		if(name == ""){
			for(int i=0;i<GameObjects.size();i++){
				T* GOi = dynamic_cast<T*>(GameObjects[i].get());
				//std::cout<<"Dynamically casting"<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					return(std::dynamic_pointer_cast<T>(GameObjects[i]));
				}
			}
		}else{
			for(int i=0;i<GameObjects.size();i++){
				T* GOi = dynamic_cast<T*>(GameObjects[i].get());
				//std::cout<<"Dynamically casting name "<<name<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					if(GameObjects[i]->name == name){
						return(std::dynamic_pointer_cast<T>(GameObjects[i]));
					}
				}
			}
		}
		//in order to get here you have to have not found either named or unnamed
		if(renderWindow){
			if(renderWindow != this){
				return(renderWindow->FindObjectRecursive<T>(name));
			}
		}
		//if(mainWindow->debug){NEVER MESS WITH THIS.  if you do IT MEANS DEATH(eg. don't try to include the main class from this file)
		//	std::cout<<"couldn't find object "<<name<<" in recursive check"<<std::endl;
		//}
		return(0);
	}
	GPU_Target* window = 0;
	std::pair<int, int> size;
	std::pair<int, int> renderSize;
	float rotation;
	std::pair<int, int> center;
	//SDL_Surface* ImageSurface = 0;
	//SDL_Texture* Texture = 0;
	GPU_Image* Image;
	GPU_Target* ImageTarget;
	std::string ImagePath = "";
	SDL_Color GetPixelColor(std::pair<int, int> pixelPos);
	void printHirearchy();
	bool parallelUpdate = false;
	bool parallelLoad = false;
	bool parallelInitialize = false;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~RenderObject();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "std::pair<float,float>"},
		{"SpawnTime", "int"},
		{"depth", "float"},
		{"name", "std::string"},
		{"size", "std::pair<int,int>"},
		{"renderSize", "std::pair<int,int>"},
		{"rotation", "float"},
		{"center", "std::pair<int,int>"},
		{"GameObjects", "std::vector<std::shared_ptr<GameObject>>"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name},
		{"size", &size},
		{"renderSize", &renderSize},
		{"rotation", &rotation},
		{"center", &center},
		{"GameObjects", &GameObjects}
	};

};

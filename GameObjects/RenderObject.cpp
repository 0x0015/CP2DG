#include "RenderObject.hpp"
#include "Sprite.hpp"
#include "../Main.hpp"
#include <algorithm>
#include <execution>
//#include "gl_core_3_0.h"

void RenderObject::Initialize(){
	for(int i=0;i<GameObjects.size();i++){
		GameObjects[i]->mainWindow = mainWindow;
		GameObjects[i]->renderWindow = this;
	}
	//for(int i=0;i<GameObjects.size();i++){
	//	GameObjects[i]->Initialize();
	//}
	if(parallelInitialize){
		//std::for_each(std::execution::par_unseq, GameObjects.begin(), GameObjects.end(), [&mainWindow, &renderWindow](std::shared_ptr<GameObject> n){
		//		n->mainWindow = mainWindow;
		//		n->renderWindow = renderWindow;});
		std::for_each(std::execution::par_unseq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){
				n->Initialize();});
	}else{
		//std::for_each(std::execution::seq, GameObjects.begin(), GameObjects.end(), [&mainWindow, &renderWindow](std::shared_ptr<GameObject> n){
		//		n->mainWindow = mainWindow;
		//		n->renderWindow = renderWindow;});
		std::for_each(std::execution::seq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){
				n->Initialize();});
	}
}
void RenderObject::Load(){
	//ImageSurface = IMG_Load(ImagePath.c_str());
	//if(!ImageSurface){
	//	std::cout<<"Image load error"<<std::endl;
	//}
	//Texture = SDL_CreateTextureFromSurface(mainWindow->renderer, Image);
	//SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
	Image = GPU_CreateImage(renderSize.first, renderSize.second, GPU_FORMAT_RGBA);
	if(!Image){
		std::cout<<"GPU_Image create error"<<std::endl;
	}
	GPU_LoadTarget(Image);
	ImageTarget = Image->target;
	window = Image->target;
	GPU_Clear(Image->target);
	//GPU_AddDepthBuffer(ImageTarget);
	if(parallelLoad){
		std::for_each(std::execution::par_unseq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){
				n->Load();});
	}else{
		std::for_each(std::execution::seq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){
				n->Load();});
	}
	//for(int i=0;i<GameObjects.size();i++){
	//	GameObjects[i]->Load();
	//}
}
void RenderObject::Draw(){
	
	GPU_SetActiveTarget(Image->target);
	GPU_Clear(Image->target);
	for(int i=0;i<GameObjects.size();i++){
		GameObjects[i]->Draw();
	}
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
void RenderObject::Update(){
	if(parallelUpdate){
		auto end = std::remove_if(std::execution::par_unseq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){return(n->toDelete);});
		//for_each(std::execution::seq, end, GameObjects.end(), [](GameObject* n){delete(n);});
		GameObjects.erase(end, GameObjects.end());
		std::for_each(std::execution::par_unseq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){n->Update();});
	}else{
		auto end = std::remove_if(std::execution::seq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){return(n->toDelete);});
		//std::cout<<"removeIf "<<&*end<<" .end() "<<&*GameObjects.end()<<std::endl;
		//for_each(std::execution::seq, end, GameObjects.end(), [](GameObject* n){std::cout<<"Deleting N: "<<n<<std::endl;delete(n);});//is this necessary?  find out next time
		GameObjects.erase(end, GameObjects.end());
		std::for_each(std::execution::seq, GameObjects.begin(), GameObjects.end(), [](std::shared_ptr<GameObject> n){n->Update();});
	}
	//for(int i=0;i<GameObjects.size();i++){
	//	if(GameObjects[i]->toDelete){
	//		delete(GameObjects[i]);
	//		GameObjects.erase(GameObjects.begin()+i);
	//		i--;
	//		continue;
	//	}else{
	//		GameObjects[i]->Update();
	//	}
	//}
	std::sort(GameObjects.begin(), GameObjects.end(), [](const std::shared_ptr<GameObject> obj1, const std::shared_ptr<GameObject> obj2){
			return(obj1->depth < obj2->depth);
			});//sort of clunky, using std::sort to sort the z buffer, but I guess it's fine.

}

SDL_Color RenderObject::GetPixelColor(std::pair<int, int> pixelPos){
	//float pixel[4];
	//glReadPixels(pixelPos.first, pixelPos.second, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	return(GPU_GetPixel(Image->target, pixelPos.first, pixelPos.second));
}

void RenderObject::printHirearchy(){
	std::cout<<"{"<<std::endl;
	for(int i=0;i<GameObjects.size();i++){
		if(dynamic_cast<RenderObject*>(GameObjects[i].get()) != 0){
			// is a render object
			std::cout<<typeid(*GameObjects[i]).name()<<" "<<GameObjects[i]->name;
			dynamic_cast<RenderObject*>(GameObjects[i].get())->printHirearchy();
		}else{
			std::cout<<typeid(*GameObjects[i]).name()<<" "<<GameObjects[i]->name<<std::endl;
		}
	}
	std::cout<<"}"<<std::endl;
}

RenderObject::~RenderObject(){
	//for(int i=0;i<GameObjects.size();i++){
	//	delete(GameObjects[i]);
	//}
	GPU_FreeTarget(window);
	GPU_FreeTarget(ImageTarget);
	GPU_FreeImage(Image);
}

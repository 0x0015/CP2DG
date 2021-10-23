#include "Main.hpp"

void Main::Initialize(){
	debug = true;
	
	resolution = std::pair<int, int>(1280, 720);
	renderSize = std::pair<int, int>(1920, 1080);

	CP2DG::Initialize();
}
void Main::Load(){
	CP2DG::Load();
}
void Main::Draw(){
	CP2DG::Draw();
}
void Main::Update(){
	CP2DG::Update();
}
Main::Main(ArguementHandler* a){
	CP2DGCreate(a);
}

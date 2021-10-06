#include "Main.hpp"

void Main::Initialize(){
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

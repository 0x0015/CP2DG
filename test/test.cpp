#include "test.hpp"

void testClass::Initialize(){

}

void testClass::Update(){

}

void testClass::Draw(){

}

void testClass::Load(){

}

testClass::testClass(){
	std::cout<<"testClass Make"<<std::endl;
}

testClass::~testClass(){
	std::cout<<"testClass deconstructor"<<std::endl;
}



std::pair<std::string, std::shared_ptr<JsonLoaderDef_Base>> getGameObject(int i){
	std::shared_ptr<JsonLoaderDef<testClass>> loaderDef = std::make_shared<JsonLoaderDef<testClass>>();
	return(std::pair<std::string, std::shared_ptr<JsonLoaderDef_Base>>("testClass", loaderDef));
}

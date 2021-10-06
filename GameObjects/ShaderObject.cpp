#include "ShaderObject.hpp"
#include "../Shader.hpp"
#include "../Main.hpp"
#include "../AssetLoader.hpp"

void ShaderObject::Initialize(){
	//shad = new Shader(Id, vert, frag);
	mainWindow->Assets->ShaderRequiredPath(frag, vert);
	//mainWindow->Assets.ImageRequiredPath("blank.png");
	//mainWindow->Assets.ImageRequiredPath("field.png");
	
	UniformF["globalTime"] = 0;
	UniformFV["resolution"] = {(float)renderResolution.first, (float)renderResolution.second};
}

void ShaderObject::Load(){
	shad = mainWindow->Assets->Shaders[std::pair<std::string, std::string>(frag, vert)];
	Image = GPU_CreateImage(size.first, size.second, GPU_FORMAT_RGBA);
	blankTexture = GPU_CreateImage(renderResolution.first, renderResolution.second, GPU_FORMAT_RGBA);
	//std::cout<<Image<<" "<<Image->target<<std::endl;
	GPU_LoadTarget(Image);
	//std::cout<<Image<<" "<<Image->target<<std::endl;
	ImageTarget = Image->target;
	GPU_Clear(Image->target);
	//blankTexture = GPU_CopyImage(mainWindow->Assets.Images["field.png"]);
	//GPU_SetImageVirtualResolution(blankTexture, renderResolution.first, renderResolution.second);

	for(int i=0;i<additionalVariables.size();i++){
		shad->addVariable(additionalVariables[i]);
	}
	for(auto it : UniformUI){
		shad->addVariable(it.first);
	}
	for(auto it : UniformI){
		shad->addVariable(it.first);
	}
	for(auto it : UniformF){
		shad->addVariable(it.first);
	}
	for(auto it : UniformIV){
		shad->addVariable(it.first);
	}
	for(auto it : UniformUIV){
		shad->addVariable(it.first);
	}
	for(auto it : UniformFV){
		shad->addVariable(it.first);
	}
	for(int i=0;i<Images.size();i++){
		shad->addImg(Images[i]);
	}

	
	//GPU_AddDepthBuffer(ImageTarget);
}
void ShaderObject::Draw(){
	GPU_SetActiveTarget(Image->target);
	GPU_Clear(Image->target);

	shad->activate();
	for(auto it : UniformUI){
		GPU_SetUniformui(shad->getVar(it.first), it.second);
	}
	for(auto it : UniformI){
		GPU_SetUniformi(shad->getVar(it.first), it.second);
	}
	for(auto it : UniformF){
		GPU_SetUniformf(shad->getVar(it.first), it.second);
	}
	for(auto it : UniformIV){
		int* vectorData = &it.second[0];
		GPU_SetUniformiv(shad->getVar(it.first), 1, it.second.size(), vectorData);
	}
	for(auto it : UniformUIV){
		unsigned int* vectorData = &it.second[0];
		GPU_SetUniformuiv(shad->getVar(it.first), it.second.size(), 1, vectorData);
	}
	for(auto it : UniformFV){
		float* vectorData = &it.second[0];
		GPU_SetUniformfv(shad->getVar(it.first), it.second.size(), 1, vectorData);
	}
	
	GPU_Blit(blankTexture, NULL, Image->target, blankTexture->w / 2.f, blankTexture->h / 2.f);
	
	GPU_DeactivateShaderProgram();
	GPU_SetActiveTarget(renderWindow->window);
	Sprite::Draw();
	GPU_Flip(Image->target);
	//GPU_SetUniformMatrixfv();
}
void ShaderObject::Update(){
	UniformF["globalTime"] = ((float)mainWindow->ticks)/60;
	//UniformF["globalTime"] = (GLfloat)SDL_GetTicks();
	Sprite::Update();
}

ShaderObject::~ShaderObject(){
	//delete(shad);
	GPU_FreeImage(blankTexture);
}

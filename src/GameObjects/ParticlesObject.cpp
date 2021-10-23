#include "GameObjects/ParticlesObject.hpp"
#include "GameObjects/RenderObject.hpp"
#include "Main.hpp"
#include "AssetLoader.hpp"
#include "ComputeShader.hpp"

void ParticlesObject::Initialize(){
	mainWindow->Assets->ComputeShaderRequiredPath("particle.cs");
}
void ParticlesObject::Load(){
	shader = mainWindow->Assets->ComputeShaders["particle.cs"];
	if(startingParticleDatas.size() > 0 && startingParticlePoses.size() > 0){
		shader->LoadDataVector<ParticlePos>(startingParticlePoses, 0);//SSbo 0 is pos
		shader->LoadDataVector<ParticleData>(startingParticleDatas, 1);//SSbo 1 is color
		startingParticlePoses.clear();
		startingParticleDatas.clear();
	}
}
void ParticlesObject::Draw(){
	//glGenBuffers(1, &(shader->SSbos[0].first));
	GPU_FlushBlitBuffer();

	ParticlePos* SSboBuffer = shader->MapBuffer<ParticlePos>(0, true);

	GPU_PrimitiveBatch(NULL, renderWindow->window, GPU_POINTS, shader->numItems, (float*)SSboBuffer, 1, NULL, GPU_BATCH_XY_RGBA);

	shader->UnmapBuffer();
	
}
void ParticlesObject::Update(){
	shader->run();
}

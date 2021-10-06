#include "CP2DG.hpp"
#include <filesystem>
#include "CppGen.hpp"
#include "InputHandler.hpp"
#include "AssetLoader.hpp"
#include "ArguementHandler/ArgHandle.hpp"
#include "GUI.hpp"
#include "audio.h"
#include "JsonLoader.hpp"
#include "GameObjects/ParticlesObject.hpp"

void CP2DG::Initialize(){
	if(debug)
		std::cout<<"Initialize"<<std::endl;
	//SDL_SetMainReady();
	//renderSize = std::pair<int, int>(1920, 1080);
	//renderRatio = 1;
	resolution = std::pair<int, int>(1280, 720);
	renderSize = std::pair<int, int>(1920, 1080);
	//renderRatio = (float)renderSize.first/1920.0;
	GPU_SetRequiredFeatures(GPU_FEATURE_RENDER_TARGETS);
	GPU_SetRequiredFeatures(GPU_FEATURE_BLEND_EQUATIONS);
	GPU_SetRequiredFeatures(GPU_FEATURE_ALL_SHADERS);
	GPU_SetRequiredFeatures(GPU_FEATURE_ALL_BASE);

	

	GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
	
	//IMG_Init(IMG_INIT_PNG);
	
	GPU_RendererID rendererID = GPU_MakeRendererID("GPU_RENDERER_OPENGL_4_3", GPU_RENDERER_OPENGL_4, 4, 3);//this is what I have to go through to get compute shaders.
	
	window = GPU_InitRendererByID(rendererID, resolution.first, resolution.second, GPU_DEFAULT_INIT_FLAGS);
	//SDL_SetWindowResizable(SDL_GetWindowFromID(window->context->windowID),SDL_TRUE);//in order to do this you would also have to check when it happens and GPU_SetWindowResolution

	//GPU_SetVirtualResolution(window, 1920, 1080);
	
	/*
	if(window == NULL || ogl_LoadFunctions() == ogl_LOAD_FAILED){
		std::cout<<"Error initalizing Opengl"<<std::endl;
		running = -1;
		return;
	}*/
	
	if(flextInit() == -1){
		std::cout<<"Failed to Load opengl."<<std::endl;
		running = -1;
		return;
	}

	std::cout<<"Successfully loaded opengl "<<FLEXT_MAJOR_VERSION<<"."<<FLEXT_MINOR_VERSION<<" with extention compute_shader="<<FLEXT_ARB_compute_shader<<", extension shader_storage_buffer_object="<<FLEXT_ARB_shader_storage_buffer_object<<std::endl;

	if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0){
		std::cout<<"Failed to initialize sdl"<<std::endl;
		running = -1;
		return;
	}

	initAudio();
	//SDL_Init(SDL_INIT_EVERYTHING);

	//GPU_SetDepthTest(window, true);
	//GPU_SetDepthWrite(window, true);
	//window->camera.z_near = 0;
	//window->camera.z_far = 65535;
	//GPU_SetDepthTest(window, true);
	GPU_SetShapeBlending(true);
	//GPU_SetShapeBlendFunction(GPU_FUNC_SRC_ALPHA, GPU_FUNC_ONE_MINUS_SRC_ALPHA, GPU_FUNC_ONE, GPU_FUNC_ZERO );
	GPU_SetShapeBlendMode(GPU_BLEND_NORMAL);

	mainWindow = this;
	renderWindow = this;

	Assets = new AssetLoader();
	Assets->mainWindow = this;
	Input = new InputHandler();

	
	std::shared_ptr<RenderObject> Level = std::make_shared<RenderObject>();
	Level->renderSize = std::pair<float, float>(renderSize.first, renderSize.second);
	Level->size = std::pair<float, float>(resolution.first, resolution.second);
	Level->depth = 0;
	GameObjects.push_back(Level);
	
	JsonLoader::levelLoadDebug = debug;
	Level->GameObjects = JsonLoader::LoadSceneFromFile("Content/Levels/Level.json");

	//MusicObject* LevelMusic = new MusicObject();
	//LevelMusic->audioPath = "Level1.wav";
	//GameObjects.push_back(LevelMusic);
	//Assets->AudioRequiredPath("Level1.wav");

	std::shared_ptr<GUI> gui = std::make_shared<GUI>();
	GameObjects.push_back(gui);
	
	/*//just for testing.  not actually wanted for the most part.
	std::shared_ptr<ParticlesObject> particleTest = std::make_shared<ParticlesObject>();
	particleTest->depth = 5;
	std::vector<ParticlePos> poses;
	std::vector<ParticleData> colors;
	for(int i=0;i<10000;i++){
		poses.push_back(ParticlePos(1920/2, 1080/2, 1, 0.5, 0, 1));
		colors.push_back(ParticleData(0, 1));
	}
	particleTest->startingParticleDatas = colors;
	particleTest->startingParticlePoses = poses;
	GameObjects.push_back(particleTest);
	*/

	//player = new Player();
	//Level->GameObjects.push_back(player);
	
	/*
	Sprite* Background = new Sprite();
	Background->position = std::pair<float, float>(0, 0);
	Background->size = std::pair<float, float>(1920, 1080);
	Background->depth = 0;
	Background->ImagePath = "sky.png";
	Assets.ImageRequiredPath("sky.png");
	Level->GameObjects.push_back(Background);
	*/

	//RenderObject* playerBullets = new RenderObject();
	//playerBullets->renderSize = std::pair<float, float>(1920, 1080);
	//playerBullets->size = std::pair<float, float>(1920, 1080);
	//playerBullets->depth = 0.5;
	//playerBullets->name = "playerBullets";
	//Level->GameObjects.push_back(playerBullets);
	
	//ShaderObject* rainS = new ShaderObject();
	//rainS->renderResolution = std::pair<float, float>(1920, 1080);
	//rainS->size = std::pair<float, float>(1920, 1080);
	//rainS->depth = 0;
	//rainS->vert = "v1.vert";
	//rainS->frag = "cloud.frag";
	//rainS->Id = "test";
	//Level->GameObjects.push_back(rainS);
	
	//EnemyCanvas* Enemies = new EnemyCanvas();
	//Enemies->mapFile = "Content/Levels/test.json";
	//Level->GameObjects.push_back(Enemies);


	//for(int i=0;i<GameObjects.size();i++){
	//	GameObjects[i]->mainWindow = this;
	//	GameObjects[i]->renderWindow = this;
	//}
	//for(int i=0;i<GameObjects.size();i++){
	//	GameObjects[i]->Initialize();
	//}
	
	RenderObject::Initialize();

	if(debug){
		printHirearchy();
	}
}
void CP2DG::Load(){
	if(debug)
		std::cout<<"Load"<<std::endl;

	Assets->LoadImages();
	Assets->LoadAudio();
	Assets->LoadFonts();
	Assets->LoadShaders();
	Assets->LoadComputeShaders();

	//playSoundFromMemory(Assets->Audios["Level1.wav"], SDL_MIX_MAXVOLUME);
	

	for(int i=0;i<GameObjects.size();i++){
		GameObjects[i]->Load();
	}
	

	std::string path = "behaviors";
	std::vector<std::string> paths;
	for(const auto & entry : std::filesystem::recursive_directory_iterator(path)){
		if(entry.path().extension() == ".cpp"){
			paths.push_back(entry.path().string());
		}
	}
	for(int i=0;i<paths.size();i++){
		std::cout<<"Found behavior:  " + paths[i]<<std::endl;
	}
	/*
	CppGen<GameObject*, int>::compilerOptions = "main.a";
	std::vector<CppGen<GameObject*, int>*> CppGens;
	for(int i=0;i<paths.size();i++){
		//std::string codeTemp = readFile(paths[i]);
		CppGen<GameObject*, int>* tempGen = new CppGen<GameObject*, int>(paths[i], true, "g++", "getGameObject");
		tempGen->generateCode();
		if(tempGen->generated == true && tempGen->error == false){
			GameObject* tempObj = tempGen->call(0);
			tempObj->mainWindow = this;
			tempObj->renderWindow = this;
			tempObj->Initialize();
			tempObj->Load();
			GameObjects.push_back(tempObj);
		}else{
			std::cout<<"Error generating " + paths[i] + ":\n";
			std::cout<<tempGen->compilerOutput<<std::endl;
			delete(tempGen);
		}
	}
	*/
}
void CP2DG::Draw(){
	GPU_Clear(window);
	GPU_MatrixMode(window, GPU_MODEL);
	GPU_PushMatrix();
	for(int i=0;i<GameObjects.size();i++){
		GameObjects[i]->Draw();
	}
	GPU_PopMatrix();
	//SDL_RenderPresent(renderer);
	GPU_Flip(window);
}
void CP2DG::Update(){
	//std::cout<<"Update"<<std::endl;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){
			running = 0;
		}else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
			Input->handleKeyboardEvent(&event);
		}else if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL){
			Input->handleMouseEvent(&event);
		}
	}
	//keyboardState = SDL_GetKeyboardState(NULL);
	//int mouseXt;
	//int mouseYt;
	//SDL_GetMouseState(&mouseXt, &mouseYt);
	//mousePos = std::pair<int, int>(mouseXt, mouseYt);
	//bool mouseLp = false;
	//bool mouseRp = false;
	//if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
	//	mouseLp = true;
	//}
	//if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
	//	mouseRp = true;
	//}
	//mouseState = std::pair<bool, bool>(mouseLp, mouseRp);
	for(int i=0;i<GameObjects.size();i++){
		if(GameObjects[i]->toDelete){
			GameObjects.erase(GameObjects.begin()+i);
		}else{
			GameObjects[i]->Update();
		}
	}

	std::sort(GameObjects.begin(), GameObjects.end(), [](const std::shared_ptr<GameObject> obj1, const std::shared_ptr<GameObject> obj2){
			return(obj1->depth < obj2->depth);
			});//sort of clunky, using std::sort to sort the z buffer, but I guess it's fine.

	Draw();
	ticks++;
}

void CP2DG::CP2DGCreate(ArguementHandler* a){
	args = a;
}

CP2DG::CP2DG(ArguementHandler* a){
	CP2DGCreate(a);
}

CP2DG::CP2DG(){}

CP2DG::~CP2DG(){
	//SDL_DestroyRenderer(renderer);
	//SDL_DestroyWindow(window);
	//IMG_Quit();
	delete(Input);
	delete(Assets);
	GPU_FreeTarget(window);
	GPU_Quit();
	SDL_Quit();
}

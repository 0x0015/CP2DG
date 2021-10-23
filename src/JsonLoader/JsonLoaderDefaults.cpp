#include "JsonLoader/JsonLoaderDefaults.hpp"
#include "GameObjects/GameObject.hpp"
#include "GameObjects/MusicObject.hpp"
#include "GameObjects/ParticlesObject.hpp"
#include "GameObjects/RenderObject.hpp"
#include "GameObjects/ShaderObject.hpp"
#include "GameObjects/Sprite.hpp"
#include "GameObjects/TextObject.hpp"

std::unordered_map<std::string, std::shared_ptr<JsonLoaderDef_Base>> JsonLoaderDefsDefault(){
	std::unordered_map<std::string, std::shared_ptr<JsonLoaderDef_Base>> output;
	output["GameObject"] = std::make_shared<JsonLoaderDef<GameObject>>();
	output["MusicObject"] = std::make_shared<JsonLoaderDef<MusicObject>>();
	output["ParticlesObject"] = std::make_shared<JsonLoaderDef<ParticlesObject>>();
	output["RenderObject"] = std::make_shared<JsonLoaderDef<RenderObject>>();
	output["ShaderObject"] = std::make_shared<JsonLoaderDef<ShaderObject>>();
	output["Sprite"] = std::make_shared<JsonLoaderDef<Sprite>>();

	return(output);
}

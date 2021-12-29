#include "JsonLoader/JsonLoader.hpp"
#include "Main.hpp"
#include "JsonLoader/json.hpp"
#include "../SimpleCppTextFileHandler/file.hpp"
#include <vector>
#include "GameObjects/GameObject.hpp"

using json = nlohmann::json;

#include "JsonLoader/JsonLoaderDefs/JsonDefaultDefs.hpp"
#include "JsonLoader/JsonLoaderDefaults.hpp"
std::unordered_map<std::string, std::shared_ptr<JsonLoadDef>> JsonLoader::JsonLoadDefs = getDefaultLoaders();//just setting default value
std::unordered_map<std::string, std::shared_ptr<JsonLoaderDef_Base>> JsonLoader::JsonLoaderDefs = JsonLoaderDefsDefault();//setting these too

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}
std::vector<std::shared_ptr<GameObject>> JsonLoader::LoadSceneFromText(std::string text){
	if(text == ""){
		std::cout<<"Json load error, text blank"<<std::endl;
		return(std::vector<std::shared_ptr<GameObject>>());
	}
	auto j = json::parse(text);
	
	if(!j.contains("GameObjects")){
		return(std::vector<std::shared_ptr<GameObject>>());
	}

	json jGOs = j["GameObjects"];

	return(LoadGameObjects(jGOs));
}

std::vector<std::shared_ptr<GameObject>> JsonLoader::LoadGameObjects(json jGOs){
	if(jGOs.contains("GameObjects")){
		//jGOs should be the gameobjects list
		return(LoadGameObjects(jGOs["GameObjects"]));
	}
	std::vector<std::shared_ptr<GameObject>> GameObjects;
	for(int i=0;i<jGOs.size();i++){
		json jGO = jGOs[i];
		std::string type = jGO["type"].get<std::string>();
		//for(int x=0;x<jGO.size();x++){
		//	std::cout<<jGO[x].get<std::string>()<<std::endl;
		//}
		
		if(levelLoadDebug){
			std::cout<<"Loading "<<type<<" object from json"<<std::endl;
		}
		
		if(!JsonLoaderDefs.contains(type)){
			std::cout<<"Loader:  Unknown type \"" + type + "\"!"<<std::endl;
			continue;//stop this attempt
		}

		std::shared_ptr<JsonLoaderDef_Arg_Wrapper> Args = std::make_shared<JsonLoaderDef_Arg_Wrapper>();
		
		for(auto& [k, v]: jGO.items()){
			std::cout<<k<<std::endl;
			std::cout<<v<<std::endl;
			if(k == "type"){
				continue;
			}
			std::optional<std::string> otype = JsonLoaderDefs[type]->getType(k);//check if the class you're loading has a member, and it's type
			if(!otype){
				std::cout<<"unknown type of variable "<<k<<std::endl;
				continue;
			}
			std::string varType = otype.value();

			if(!JsonLoadDefs.contains(varType)){
				std::cout<<"unknown type:  "<<varType<<std::endl;
				continue;
			}

			JsonLoadDefs[varType]->load(v);
			Args->addValueFromVoid(k, varType, JsonLoadDefs[varType]->getSharedVoid());
		}
		//hopefuly now Args should have all the correct args
		std::shared_ptr<GameObject> tempObject = JsonLoaderDefs[type]->createGameObject(Args);
		GameObjects.push_back(tempObject);
	}
	
	return(GameObjects);
}
std::vector<std::shared_ptr<GameObject>> JsonLoader::LoadSceneFromFile(std::string filename){
	if(filename == ""){
		return(std::vector<std::shared_ptr<GameObject>>());
	}
	std::string jsonSceneLoadText = readFile(filename);
	if(jsonSceneLoadText == ""){
		jsonSceneLoadText = readFile("Content/Levels/" + filename + ".json");
	}
	std::vector<std::shared_ptr<GameObject>> loaded = LoadSceneFromText(jsonSceneLoadText);
	return(loaded);
}

void JsonLoader::SaveSceneToFile(std::string file){//not needed, yet so let's just leave an empty decleration.

}

/*
Basically how this works is in each GameObject it has a list(map) of what members it needs and what types they are(stored as strings).
additionally it has another map, which maps the names of the members(strings) to the actual members themselves(void*s).

then the json is read and it uses Definitions from the JsonLoadDefs list to load the types that the class needs for it's members, which is stored in a JsonLoaderDef_Arg_Wrapper.

lastly based on the type of class you want(stored as a string) you put the args into a member of JsonLoaderDefs list and get out a GameObject which was casted from that type.

overall the usefulness is that I won't have to make new definitions(for how they load from json) for each class manually, and can put them in the classes themselves.
*/

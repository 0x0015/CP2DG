#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>
#include "json.hpp"
#include "JsonLoaderDefs/JsonLoadDef.hpp"

class GameObject;

class JsonLoaderDef_Arg_Wrapper{
public:
	std::map<std::string, std::pair<std::string, std::shared_ptr<void>>> values;//name, type, value
	template<typename T> T get(std::string name){
		return(*std::static_pointer_cast<T>(values[name].second));
	}
	std::string getType(std::string name){
		return(values[name].first);
	}
	template<typename T> void addValue(std::string name, std::string type, T& value){
		std::shared_ptr<T> valuePlaceholder = std::make_shared<T>();
		*valuePlaceholder = value;
		std::shared_ptr<void> voidPlaceholder = std::static_pointer_cast<void>(valuePlaceholder);
		values[name] = std::pair<std::string, std::shared_ptr<void>>(type, voidPlaceholder);
	}
	void addValueFromVoid(std::string name, std::string type, std::shared_ptr<void> value){
		values[name] = std::pair<std::string, std::shared_ptr<void>>(type, value);
	}
};

class JsonLoaderDef_Base{
public:
	virtual std::pair<int,int> matches(std::map<std::string, std::string> types){
		return(std::pair<int,int>(0,0));//<int1, int,> int1=number of correct matches int2 = number of incorrect matches
	}
	virtual std::optional<std::string> getType(std::string name){
		return(std::nullopt);
	}
	virtual std::shared_ptr<GameObject> createGameObject(std::shared_ptr<JsonLoaderDef_Arg_Wrapper> args){
		return(std::shared_ptr<GameObject>(0));
	}
};

template <typename T> class JsonLoaderDef : public JsonLoaderDef_Base{
public:
	std::optional<std::string> getType(std::string name){
		if(!T::Blueprint.contains(name)){
			return(std::nullopt);
		}
		return(T::Blueprint[name]);
	}
	std::shared_ptr<T> create(std::shared_ptr<JsonLoaderDef_Arg_Wrapper> args){
		std::shared_ptr<T> output = std::make_shared<T>();
		for(auto i : args->values){
			if(!T::Blueprint.contains(i.first)){//if the arg doesn't match an arg that the class can take cancel
				std::cout<<"class does not contain member "<<i.first<<std::endl;
				continue;
			}
			if(i.second.first == "int" && T::Blueprint[i.first] == "int"){
				void* val = output->Create_Bp[i.first];
				int* ival = (int*)val;
				*ival = args->get<int>(i.first);
			}else if(i.second.first == "float" && T::Blueprint[i.first] == "float"){
				void* val = output->Create_Bp[i.first];
				float* ival = (float*)val;
				*ival = args->get<float>(i.first);
			}else if(i.second.first == "double" && T::Blueprint[i.first] == "double"){
				void* val = output->Create_Bp[i.first];
				double* ival = (double*)val;
				*ival = args->get<double>(i.first);
			}else if(i.second.first == "std::string" && T::Blueprint[i.first] == "std::string"){
				void* val = output->Create_Bp[i.first];
				std::string* ival = (std::string*)val;
				*ival = args->get<std::string>(i.first);
			}else if(i.second.first == "std::pair<float,float>" && T::Blueprint[i.first] == "std::pair<float,float>"){
				void* val = output->Create_Bp[i.first];
				std::pair<float,float>* ival = (std::pair<float,float>*)val;
				*ival = args->get<std::pair<float,float>>(i.first);
			}else if(i.second.first == "std::pair<int,int>" && T::Blueprint[i.first] == "std::pair<int,int>"){
				void* val = output->Create_Bp[i.first];
				std::pair<int,int>* ival = (std::pair<int,int>*)val;
				*ival = args->get<std::pair<int,int>>(i.first);
			}else if(i.second.first == "std::vector<std::shared_ptr<GameObject>>" && T::Blueprint[i.first] == "std::vector<std::shared_ptr<GameObject>>"){
				void* val = output->Create_Bp[i.first];
				std::vector<std::shared_ptr<GameObject>>* ival = (std::vector<std::shared_ptr<GameObject>>*)val;
				*ival = args->get<std::vector<std::shared_ptr<GameObject>>>(i.first);
			}else{//I need to remember to clean this up some day.
				std::cout<<"unknown type: "<<i.first<<" "<<i.second.first<<std::endl;
			}
		}
		return(output);
	}
	std::shared_ptr<GameObject> createGameObject(std::shared_ptr<JsonLoaderDef_Arg_Wrapper> args){
		std::shared_ptr<T> gameObj = create(args);
		return(std::static_pointer_cast<GameObject>(gameObj));
	}
};

class JsonLoader{
public:
	static inline bool levelLoadDebug = false;
	static std::unordered_map<std::string, std::shared_ptr<JsonLoaderDef_Base>> JsonLoaderDefs;
	static std::vector<std::shared_ptr<GameObject>> LoadGameObjects(nlohmann::json jGOs);
	static std::vector<std::shared_ptr<GameObject>> LoadSceneFromText(std::string text);
	static std::vector<std::shared_ptr<GameObject>> LoadSceneFromFile(std::string file);
	static void SaveSceneToFile(std::string file);
	static std::string SaveSceneToText();

	static std::unordered_map<std::string, std::shared_ptr<JsonLoadDef>> JsonLoadDefs;

	//std::unordered_map<std::string, 
};


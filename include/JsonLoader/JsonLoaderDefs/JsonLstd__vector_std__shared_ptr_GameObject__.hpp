#pragma once
#include "JsonLoadDef.hpp"

class GameObject;

class JsonLstd__vector_std__shared_ptr_GameObject__ : public JsonLoadDef{
public:
	std::string type = "std::vector<std::shared_ptr<GameObject>>";
	void load(json& j);
	std::vector<std::shared_ptr<GameObject>> value;
	std::shared_ptr<void> getSharedVoid();
};

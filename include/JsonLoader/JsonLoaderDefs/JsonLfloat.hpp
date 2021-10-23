#pragma once
#include "JsonLoadDef.hpp"

class JsonLfloat : public JsonLoadDef{
public:
	std::string type = "float";
	void load(json& j);
	float value;
	std::shared_ptr<void> getSharedVoid();
};

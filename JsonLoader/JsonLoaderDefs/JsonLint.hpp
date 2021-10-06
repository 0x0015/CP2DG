#pragma once
#include "JsonLoadDef.hpp"

class JsonLint : public JsonLoadDef{
public:
	std::string type = "int";
	void load(json& j);
	int value;
	std::shared_ptr<void> getSharedVoid();
};

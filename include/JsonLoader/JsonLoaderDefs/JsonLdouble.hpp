#pragma once
#include "JsonLoadDef.hpp"

class JsonLdouble : public JsonLoadDef{
public:
	std::string type = "double";
	void load(json& j);
	double value;
	std::shared_ptr<void> getSharedVoid();
};

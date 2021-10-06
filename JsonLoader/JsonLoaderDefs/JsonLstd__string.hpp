#pragma once
#include "JsonLoadDef.hpp"

class JsonLstd__string : public JsonLoadDef{
public:
	std::string type = "std::string";
	void load(json& j);
	std::string value;
	std::shared_ptr<void> getSharedVoid();
};

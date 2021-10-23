#pragma once
#include "JsonLoadDef.hpp"

class JsonLstd__pair_float_float_ : public JsonLoadDef{
public:
	std::string type = "std::pair<float,float>";
	void load(json& j);
	std::pair<float, float> value;
	std::shared_ptr<void> getSharedVoid();
};

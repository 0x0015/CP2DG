#pragma once
#include "JsonLoadDef.hpp"

class JsonLstd__pair_int_int_ : public JsonLoadDef{
public:
	std::string type = "std::pair<int,int>";
	void load(json& j);
	std::pair<int, int> value;
	std::shared_ptr<void> getSharedVoid();
};

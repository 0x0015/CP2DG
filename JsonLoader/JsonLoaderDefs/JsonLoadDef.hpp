#pragma once
#include <iostream>
#include <memory>
#include <optional>
#include "../json.hpp"
using json = nlohmann::json;

class JsonLoadDef{
public:
	std::string type;
	virtual void load(json& j);
	void* vvalue;
	template<typename T> std::optional<T> getValue(){
		return( *((T*)vvalue));
	}
	virtual std::shared_ptr<void> getSharedVoid();
	template<typename T> std::shared_ptr<void> convertToVoid(std::shared_ptr<T> v){
		return(std::static_pointer_cast<void>(v));
	}
};

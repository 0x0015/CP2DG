#include "JsonLoader/JsonLoaderDefs/JsonLint.hpp"

void JsonLint::load(json& j){
	value = j.get<int>();
	vvalue = &value;
}

std::shared_ptr<void> JsonLint::getSharedVoid(){
	std::shared_ptr<int> temp = std::make_shared<int>();
	*temp = value;
	return(convertToVoid<int>(temp));
}

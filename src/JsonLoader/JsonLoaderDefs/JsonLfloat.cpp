#include "JsonLoader/JsonLoaderDefs/JsonLfloat.hpp"

void JsonLfloat::load(json& j){
	value = j.get<float>();
	vvalue = &value;
}

std::shared_ptr<void> JsonLfloat::getSharedVoid(){
	std::shared_ptr<float> temp = std::make_shared<float>();
	*temp = value;
	return(convertToVoid<float>(temp));
}

#include "JsonLoader/JsonLoaderDefs/JsonLstd__string.hpp"

void JsonLstd__string::load(json& j){
	value = j.get<std::string>();
	vvalue = &value;
}

std::shared_ptr<void> JsonLstd__string::getSharedVoid(){
	std::shared_ptr<std::string> temp = std::make_shared<std::string>();
	*temp = value;
	return(convertToVoid<std::string>(temp));
}

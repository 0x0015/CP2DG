#include "JsonLoader/JsonLoaderDefs/JsonLdouble.hpp"

void JsonLdouble::load(json& j){
	value = j.get<double>();
	vvalue = &value;
}

std::shared_ptr<void> JsonLdouble::getSharedVoid(){
	std::shared_ptr<double> temp = std::make_shared<double>();
	*temp = value;
	return(convertToVoid<double>(temp));
}

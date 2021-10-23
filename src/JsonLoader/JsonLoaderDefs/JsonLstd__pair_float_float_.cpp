#include "JsonLoader/JsonLoaderDefs/JsonLstd__pair_float_float_.hpp"

void JsonLstd__pair_float_float_::load(json& j){
	value.first = j[0].get<float>();
	value.second = j[1].get<float>();
	vvalue = &value;
}

std::shared_ptr<void> JsonLstd__pair_float_float_::getSharedVoid(){
	std::shared_ptr<std::pair<float,float>> temp = std::make_shared<std::pair<float,float>>();
	*temp = value;
	return(convertToVoid<std::pair<float,float>>(temp));
}

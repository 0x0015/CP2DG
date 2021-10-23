#include "JsonLoader/JsonLoaderDefs/JsonLstd__pair_int_int_.hpp"

void JsonLstd__pair_int_int_::load(json& j){
	value.first = j[0].get<int>();
	value.second = j[1].get<int>();
	vvalue = &value;
}

std::shared_ptr<void> JsonLstd__pair_int_int_::getSharedVoid(){
	std::shared_ptr<std::pair<int,int>> temp = std::make_shared<std::pair<int,int>>();
	*temp = value;
	return(convertToVoid<std::pair<int,int>>(temp));
}

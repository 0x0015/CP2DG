#include "JsonLoader/JsonLoaderDefs/JsonLstd__vector_std__shared_ptr_GameObject__.hpp"
#include "JsonLoader/JsonLoader.hpp"

void JsonLstd__vector_std__shared_ptr_GameObject__::load(json& j){
	value = JsonLoader::LoadGameObjects(j);
	vvalue = &value;
}

std::shared_ptr<void> JsonLstd__vector_std__shared_ptr_GameObject__::getSharedVoid(){
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> temp = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();
	*temp = value;
	return(convertToVoid<std::vector<std::shared_ptr<GameObject>>>(temp));
}

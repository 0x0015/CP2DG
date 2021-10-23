#include "JsonLoader/JsonLoaderDefs/JsonLoadDef.hpp"

void JsonLoadDef::load(json& j){

}

std::shared_ptr<void> JsonLoadDef::getSharedVoid(){
	return(std::static_pointer_cast<void>(std::make_shared<char>()));//just returns a pointer to a single byte.  has to return a pointer to something one way or another
}

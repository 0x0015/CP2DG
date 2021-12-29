#include "JsonLoader/JsonLoaderDefs/JsonDefaultDefs.hpp"
#include "JsonLoader/JsonLoaderDefs/JsonLstd__pair_int_int_.hpp"
#include "JsonLoader/JsonLoaderDefs/JsonLdouble.hpp"
#include "JsonLoader/JsonLoaderDefs/JsonLstd__pair_float_float_.hpp"
#include "JsonLoader/JsonLoaderDefs/JsonLfloat.hpp"
#include "JsonLoader/JsonLoaderDefs/JsonLstd__string.hpp"
#include "JsonLoader/JsonLoaderDefs/JsonLint.hpp"
#include "JsonLoader/JsonLoaderDefs/JsonLstd__vector_std__shared_ptr_GameObject__.hpp"

std::unordered_map<std::string, std::shared_ptr<JsonLoadDef>> getDefaultLoaders(){
	std::unordered_map<std::string, std::shared_ptr<JsonLoadDef>> output;

	output["int"] = std::make_shared<JsonLint>();
	output["float"] = std::make_shared<JsonLfloat>();
	output["double"] = std::make_shared<JsonLdouble>();
	output["std::string"] = std::make_shared<JsonLstd__string>();
	output["std::pair<int,int>"] = std::make_shared<JsonLstd__pair_int_int_>();
	output["std::pair<float,float>"] = std::make_shared<JsonLstd__pair_float_float_>();//this name is horrendous
	output["std::vector<std::shared_ptr<GameObject>>"] = std::make_shared<JsonLstd__vector_std__shared_ptr_GameObject__>();//this is the only thing that could be worse.

	return(output);
}

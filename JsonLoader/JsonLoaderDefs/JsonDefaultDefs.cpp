#include "JsonDefaultDefs.hpp"
#include "JsonLstd__pair_int_int_.hpp"
#include "JsonLdouble.hpp"
#include "JsonLstd__pair_float_float_.hpp"
#include "JsonLfloat.hpp"
#include "JsonLstd__string.hpp"
#include "JsonLint.hpp"

std::unordered_map<std::string, std::shared_ptr<JsonLoadDef>> getDefaultLoaders(){
	std::unordered_map<std::string, std::shared_ptr<JsonLoadDef>> output;

	output["int"] = std::make_shared<JsonLint>();
	output["float"] = std::make_shared<JsonLfloat>();
	output["double"] = std::make_shared<JsonLdouble>();
	output["std::string"] = std::make_shared<JsonLstd__string>();
	output["std::pair<int,int>"] = std::make_shared<JsonLstd__pair_int_int_>();
	output["std::pair<float,float>"] = std::make_shared<JsonLstd__pair_float_float_>();//this name is horrendous

	return(output);
}

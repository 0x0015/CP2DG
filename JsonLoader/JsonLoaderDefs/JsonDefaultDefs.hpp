#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include "JsonLoadDef.hpp"

std::unordered_map<std::string, std::shared_ptr<JsonLoadDef>> getDefaultLoaders();

#pragma once
#include <iostream>
#include "tinyfiledialogs/tinyfiledialogs.h"

void reportError(std::string error, std::string title = "Error"){
	tinyfd_messageBox(title.c_str(), error.c_str(), "ok", "error", 1);
}

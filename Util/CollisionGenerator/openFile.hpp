#pragma once
#include <iostream>
#include "tinyfiledialogs/tinyfiledialogs.h"
#include "reportError.hpp"

std::string openFile(){
	//QString fileName = QFileDialog::getOpenFileName(this, "Open File","", "Files (.)");
	//char const * lFilterPatterns[2]={"*.png","*.jpg"};
	const char* filename = tinyfd_openFileDialog("Chose Image", "", 0, NULL, "image files", 0);
	if(filename == ""){
		std::cout<<"Please select an image and try again."<<std::endl;
		tinyfd_messageBox("Warning", "Please select an image and try again.", "ok", "warning" , 1);
		exit(-1);
	}
	return(std::string(filename));
}

std::string saveFile(std::string path){
	//QString fileName = QFileDialog::getOpenFileName(this, "Open File","", "Files (.)");
	//char const * lFilterPatterns[2]={"*.png","*.jpg"};
	const char* filename = tinyfd_saveFileDialog("Chose Image", path.c_str(), 0, NULL, "image files");
	if(filename == ""){
		std::cout<<"Please select an image and try again."<<std::endl;
		tinyfd_messageBox("Warning", "Please select an image and try again.", "ok", "warning" , 1);
		exit(-1);
	}
	return(std::string(filename));
}

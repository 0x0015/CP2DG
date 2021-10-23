#pragma once
#include <iostream>
#include <SDL2/SDL_gpu.h>
#include <vector>
#include "flextGL.h"
#include <functional>

//see https://web.engr.oregonstate.edu/~mjb/cs557/Handouts/compute.shader.1pp.pdf

class ComputeShader{
public:
	GLuint shader = 0;
	GLuint shaderProgram = 0;
	int numItems;
	int workGroupSize = 128;
	std::vector<std::pair<GLuint, size_t>> SSbos;

	int startingBaseBufferNum = 4;//idk why I want this

	ComputeShader(const std::string& shad);
	void LoadData(const void* data, size_t size, int SSbo);
	template<typename T> void LoadDataVector(std::vector<T>& items, int SSbo){
		void* data = static_cast<void*>(items.data());
		std::cout<<"loading the data vector with "<<typeid(T).name()<<" and size = "<<items.size() * sizeof(T)<<" to SSbo "<<SSbo<<std::endl;
		numItems = items.size();
		LoadData(data, items.size() * sizeof(T), SSbo);
	}

	template<typename T> void LoadDataCalculation(std::function<T(int)> func, int times, int SSbo){//this is c++, why use (T*)(int) over std::function
		while(SSbos.size() <= SSbo){
			SSbos.push_back(std::pair<GLuint, size_t>(0, 0));
		}	

		size_t size = sizeof(T) * times;
		
		glGenBuffers(1, &(SSbos[SSbo].first));
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSbos[SSbo].first);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_STATIC_DRAW);

		GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
		T* SSboBuffer= (T*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, bufMask);

		for(int i=0;i<times;i++){
			SSboBuffer[i] = func(i);
		}

		SSbos[SSbo].second = size;

		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		numItems = times;
	}
	template<typename T> void LoadDataValue(T item, int times, int SSbo){
		while(SSbos.size() <= SSbo){
			SSbos.push_back(std::pair<GLuint, size_t>(0, 0));
		}	

		size_t size = sizeof(T) * times;
		
		glGenBuffers(1, &(SSbos[SSbo].first));
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSbos[SSbo].first);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_STATIC_DRAW);

		GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
		T* SSboBuffer= (T*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, bufMask);

		for(int i=0;i<times;i++){
			SSboBuffer[i] = item;
		}

		SSbos[SSbo].second = size;

		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		numItems = times;
	}
	template<typename T> T* MapBuffer(int SSbo, bool readOnly = false){
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSbos[SSbo].first);
		T* SSboBuffer;
		if(readOnly){
			SSboBuffer = (T*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		}else{
			SSboBuffer = (T*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
		}
		return(SSboBuffer);
	}
	void UnmapBuffer();
	void run();
	~ComputeShader();
};

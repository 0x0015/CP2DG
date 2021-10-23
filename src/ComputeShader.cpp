#include "ComputeShader.hpp"
#include "SimpleCppTextFileHandler/file.hpp"

//see https://web.engr.oregonstate.edu/~mjb/cs557/Handouts/compute.shader.1pp.pdf

ComputeShader::ComputeShader(const std::string& shad){
		GLint success = 0;
		GLchar infoLog[512];

		shader = glCreateShader(GL_COMPUTE_SHADER);
		if(glGetError() != 0){
			std::cout<<"Failed to create compute shader"<<std::endl;
		}
		std::string shaderTextStr = readFile(shad);
		const char* shaderText = shaderTextStr.c_str();
		int shaderTextLength = shaderTextStr.length();
		glShaderSource(shader, 1, &shaderText, &shaderTextLength);//doesn't allow &shad.c_str()
		if(glGetError() != 0){
			std::cout<<"shader source error"<<std::endl;
		}
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if(!shader || glGetError() != 0 || success == GL_FALSE){
			std::cout<<"Failed to load compute shader."<<std::endl;
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout<<infoLog<<std::endl;
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, shader);
		glLinkProgram(shaderProgram);
		if(!shaderProgram || glGetError() != 0){
			std::cout<<"Failed to link compute shader."<<std::endl;
		}
	}
void ComputeShader::LoadData(const void* data, size_t size, int SSbo){
		while(SSbos.size() <= SSbo){
			SSbos.push_back(std::pair<GLuint, size_t>(0, 0));
		}

		glGenBuffers(1, &(SSbos[SSbo].first));
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSbos[SSbo].first);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_STATIC_DRAW);

		GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
		void* SSboBuffer= glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, bufMask);

		//size_t cpySize = std::min(size, numItems * itemSize);

		memcpy(SSboBuffer, data, size);

		SSbos[SSbo].second = size;

		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}

void ComputeShader::UnmapBuffer(){
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}
void ComputeShader::run(){
		//std::cout<<"Running compute shader, SSbos: ";
		for(int i=0;i<SSbos.size();i++){
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i+startingBaseBufferNum, SSbos[i].first);
			//std::cout<<SSbos[i].first<<" "<<SSbos[i].second<<" ";
		}
		//std::cout<<std::endl;

		glUseProgram(shaderProgram);
		glDispatchCompute(numItems/workGroupSize, 1, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		
		GPU_DeactivateShaderProgram();//make sure to get back to the normal program
	}
ComputeShader::~ComputeShader(){
		
	}


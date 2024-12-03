#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

// shader manager class

class ShaderManager
{
private:
	unsigned int shaderProgram;
	const char* vertexShaderPath = "C:\\Users\\mahmu\\Desktop\\codez\\vs\\cpp\\vsort\\vsort\\src\\shaders\\vrtxone.vert";
	const char* fragmentShaderPath = "C:\\Users\\mahmu\\Desktop\\codez\\vs\\cpp\\vsort\\vsort\\src\\shaders\\frgone.frag";
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
public:
	ShaderManager();
	~ShaderManager();
	bool createShaderProgram();
	const std::string shaderReaderFromFile(const char* shaderPath);
	bool shaderWriterToFile(const char* shaderPath, const char* shaderSource);
	bool compileShaders();	
	void useShaderProgram();
	void deleteShaderProgram();
	unsigned int getShaderProgram();
};

#endif // SHADER_MANAGER_H

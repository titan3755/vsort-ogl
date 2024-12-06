#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <shader_manager.h>
#include <visualsort.h>
#include <rectangle.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef APPLICATION_H
#define APPLICATION_H

// opengl application class
class Application
{
private:
	GLFWwindow* window;
	int width;
	int height;
	const char* title;
	bool isRunning;
public:
	Application(int width, int height, const char* title);
	~Application();
	void run();
	void fpsCalculate();
	void processInput();
	void printOpenGLInfo();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // APPLICATION_H
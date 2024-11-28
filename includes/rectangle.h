#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_manager.h>
#include <application.h>

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
private:
	unsigned int VAO, VBO, EBO;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 color;
	glm::mat4 model;
public:
	//Rectangle();
	//~Rectangle();
	//void createRectangle();
	//void drawRectangle(ShaderManager& shaderManager);
	//void setPosition(glm::vec3 position);
	//void setScale(glm::vec3 scale);
	//void setColor(glm::vec3 color);
	//glm::vec3 getPosition();
	//glm::vec3 getScale();
	//glm::vec3 getColor();
	//glm::mat4 getModel();
	// to be impleted later ---
};

#endif // RECTANGLE_H


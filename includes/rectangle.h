#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    Rectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color);
    void setup(glm::vec2 position, glm::vec2 size, glm::vec3 color);
    void setupBuffers();
    void deleteObj();
    void draw(unsigned int mLoc);
    void transform(glm::vec2 displacement);
    void rotate(float angle, glm::vec3 axis);
    void scaleRect(glm::vec2 scaleFactor);
    void setColor(glm::vec3 color);
    void setPosition(glm::vec2 position);
	void resetModelAndSetPosition(glm::vec2 position, unsigned int mLoc);
    void setScale(glm::vec2 scale);
    void setModel(glm::mat4 model);
    glm::vec3 getColor();
    glm::vec3 getPosition();
    glm::vec3 getScale();
	glm::vec2 getSize();
    glm::mat4 getModel();
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 scale;
    glm::vec3 color;
    glm::mat4 model;

private:
    GLuint VAO, VBO, EBO;
};

#endif // RECTANGLE_H

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class Rectangle {
public:
    Rectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color);
    ~Rectangle();
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

private:
    void setupBuffers();

    GLuint VAO, VBO, EBO;
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 scale;
    glm::vec3 color;
    glm::mat4 model;
};

#endif // RECTANGLE_H

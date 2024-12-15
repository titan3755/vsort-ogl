#include "Rectangle.h"

Rectangle::Rectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color)
{
	setup(position, size, color);
}

void Rectangle::setup(glm::vec2 position, glm::vec2 size, glm::vec3 color) 
{
	this->position = glm::vec3(position, 0.0f);
	this->size = glm::vec3(size, 0.0f);
	this->scale = glm::vec3(size, 0.0f);
	this->color = color;
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(this->model, this->position);  // Apply initial translation
	this->model = glm::scale(this->model, this->scale);         // Apply initial scaling
}

void Rectangle::setupBuffers()
{
    float vertices[] = {
        // positions                                    // colors
        position.x + size.x, position.y + size.y, 0.0f, color.r, color.g, color.b, // top right
        position.x + size.x, position.y - size.y, 0.0f, color.r, color.g, color.b, // bottom right
        position.x - size.x, position.y - size.y, 0.0f, color.r, color.g, color.b, // bottom left
        position.x - size.x, position.y + size.y, 0.0f, color.r, color.g, color.b  // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//Rectangle::Rectangle(glm::vec2 position, glm::vec2 size, glm::vec3 color)
//{
//    this->position = glm::vec3(position, 0.0f);
//    this->size = glm::vec3(size, 0.0f);
//    this->scale = glm::vec3(size, 0.0f);
//    this->color = color;
//    this->model = glm::mat4(1.0f);
//    this->model = glm::translate(this->model, this->position);  // Apply initial translation
//    this->model = glm::scale(this->model, this->scale);         // Apply initial scaling
//    setupBuffers();
//}
//
//Rectangle::~Rectangle()
//{
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//}


void Rectangle::deleteObj()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Rectangle::draw(unsigned int mLoc)
{
    if (mLoc == -1) {
        std::cerr << "Error: Invalid uniform location" << std::endl;
        return;
    }

    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(this->model));  // Update the model matrix in the shader
    
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Rectangle::transform(glm::vec2 displacement)
{
    this->position += glm::vec3(displacement, 0.0f);  // Update position
    this->model = glm::translate(this->model, glm::vec3(displacement, 0.0f));  // Apply translation incrementally
}

void Rectangle::rotate(float angle, glm::vec3 axis)
{
    this->model = glm::rotate(this->model, glm::radians(angle), axis);  // Apply rotation
}

void Rectangle::scaleRect(glm::vec2 scaleFactor)
{
    this->scale += glm::vec3(scaleFactor, 0.0f);  // Update scale incrementally
    this->model = glm::scale(this->model, glm::vec3(scaleFactor, 1.0f));  // Apply scaling incrementally
}

void Rectangle::setColor(glm::vec3 color)
{
    this->color = color;
}

void Rectangle::setPosition(glm::vec2 position)
{
    glm::vec3 displacement = glm::vec3(position - glm::vec2(this->position.x, this->position.y), 0.0f);
    this->position = glm::vec3(position, 0.0f);
    this->model = glm::translate(this->model, displacement);  // Update position incrementally
}

void Rectangle::resetModelAndSetPosition(glm::vec2 position, unsigned int mLoc)
{
    this->position = glm::vec3(position, 0.0f);
    this->model = glm::mat4(1.0f);  // Reset to identity matrix
    this->model = glm::translate(this->model, this->position);  // Apply translation
    this->model = glm::scale(this->model, this->scale);  // Apply scaling
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(this->model));  // Update uniform
}

void Rectangle::setScale(glm::vec2 scale)
{
    this->scale = glm::vec3(scale, 1.0f);  // Update scale
    this->model = glm::scale(this->model, glm::vec3(scale, 1.0f));  // Apply scaling incrementally
}

void Rectangle::setModel(glm::mat4 model)
{
    this->model = model;
}

glm::vec3 Rectangle::getColor()
{
    return this->color;
}

glm::vec3 Rectangle::getPosition()
{
    return this->position;
}

glm::vec3 Rectangle::getScale()
{
    return this->scale;
}

glm::vec2 Rectangle::getSize()
{
	return glm::vec2(this->size.x, this->size.y);
}

glm::mat4 Rectangle::getModel()
{
    return this->model;
}

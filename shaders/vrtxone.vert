#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 model;
uniform mat4 projection;
out vec3 vertexColor;
void main()
{
    gl_Position = model*projection*vec4(aPos, 1.0);
    vertexColor = aColor;
}
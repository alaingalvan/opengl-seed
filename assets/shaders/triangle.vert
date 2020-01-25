#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 vColor;

void main()
{
    vColor = inColor;
    gl_Position = vec4(inPosition, 1.0);
}
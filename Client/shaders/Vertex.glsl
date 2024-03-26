#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoords;

void main()
{
    gl_Position = model * vec4(inPosition.xyz, 1.0f);
    texCoords = inUV;
}
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec2 TexCoords;

uniform mat4 TRS;
uniform mat4 VP;

void main()
{
    TexCoords = aTex;
    gl_Position = VP * TRS * vec4(aPos, 1.0);
}
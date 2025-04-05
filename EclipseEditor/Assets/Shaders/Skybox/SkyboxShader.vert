#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTex;

out vec3 TexCoords;

uniform mat4 VP;

void main()
{
    vec4 pos = VP * vec4(aPos, 0.0f);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    TexCoords = aPos;
}
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
const vec2 quadVertices[4] = { vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(-1.0, 1.0), vec2(1.0, 1.0) };
const vec2 quadTextCoords[4] = { vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0) };

out vec2 TexCoords;

void main()
{
    TexCoords = quadTextCoords[gl_VertexID];
    
    gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
}
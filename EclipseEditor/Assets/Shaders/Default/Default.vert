#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out VS_OUT {
    vec3 FragPos;
    vec3 TexCoords;
    vec3 Normal;
} vs_out;

uniform mat4 VP;
uniform mat4 TRS = mat4(vec4(1.0, 0.0, 0.0, 0.0),
                        vec4(0.0, 1.0, 0.0, 0.0),
                        vec4(0.0, 0.0, 1.0, 0.0),
                        vec4(0.0, 0.0, 0.0, 1.0));

void main()
{
    vs_out.FragPos = vec3(TRS * vec4(aPos, 1.0));
    vs_out.TexCoords = vec3(aTex, 0.0);
    vs_out.Normal = mat3(transpose(inverse(TRS))) * aNorm;
    gl_Position = VP * TRS * vec4(aPos, 1.0);
}
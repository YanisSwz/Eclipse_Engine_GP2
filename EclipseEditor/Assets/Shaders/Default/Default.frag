#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, vec2(fs_in.TexCoords));
}
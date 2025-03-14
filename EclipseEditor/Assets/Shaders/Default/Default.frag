#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 TexCoords;
    vec3 Normal;
} fs_in;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = texture(tex0, vec2(fs_in.TexCoords));
}
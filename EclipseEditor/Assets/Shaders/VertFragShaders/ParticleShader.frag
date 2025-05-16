#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 TextCoords;

uniform int bHasTexture;
uniform sampler2D text0;

void main()
{
	if (bHasTexture == 0)
		FragColor = color;
	else
		FragColor = color * texture(text0, TextCoords);   
}
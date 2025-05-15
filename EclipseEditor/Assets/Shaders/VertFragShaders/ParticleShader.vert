#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTex;

struct s_particleData
{ 
    vec4 color;
    vec3 position;
    float size;
};

layout (std140) uniform particleDataBlock
{
    s_particleData particleData[2000];
} block_particleData;

uniform mat4 View;
uniform mat4 Proj;
uniform int bIsBillboard;

out vec4 color;
out vec2 TextCoords;

void main()
{
    color = block_particleData.particleData[gl_InstanceID].color;
    TextCoords = aTex;

    vec3 particlePos;
    float particleSize = block_particleData.particleData[gl_InstanceID].size / 100.0; // Divide the size by 100 to make it smaller
    if (bIsBillboard == 1)
	{
        vec3 CameraRight_worldspace = vec3(View[0][0], View[1][0], View[2][0]);
        vec3 CameraUp_worldspace = vec3(View[0][1], View[1][1], View[2][1]);

        particlePos = vec3(block_particleData.particleData[gl_InstanceID].position
            + CameraRight_worldspace * aPos.x * particleSize
            + CameraUp_worldspace * aPos.y * particleSize);
	}
    else
    {
        particlePos = block_particleData.particleData[gl_InstanceID].position
		+ aPos * particleSize;
    }

    gl_Position = Proj * View * vec4(particlePos, 1.0); 
}
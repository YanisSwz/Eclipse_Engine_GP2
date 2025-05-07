#version 330 core

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

uniform mat4 VP;
uniform float windowWidth;
uniform float windowHeight;

out VS_OUT {
    vec4 color;
    float size;
    float windowWidth;
    float windowHeight;
} vs_out;

void main()
{
    vs_out.color = block_particleData.particleData[gl_InstanceID].color;
    vs_out.size = block_particleData.particleData[gl_InstanceID].size;
    vs_out.windowWidth = windowWidth;
    vs_out.windowHeight = windowHeight;
    vs_out.size = block_particleData.particleData[gl_InstanceID].size;
    gl_Position = VP * vec4(block_particleData.particleData[gl_InstanceID].position, 1.0); 
}
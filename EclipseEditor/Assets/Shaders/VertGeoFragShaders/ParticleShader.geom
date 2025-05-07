#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec4 color;
    float size;
    float windowWidth;
    float windowHeight;
} gs_in[];

out vec4 fColor;

void build_square(vec4 position)
{    
    float halfSizeX = gs_in[0].size * 0.5 / gs_in[0].windowWidth;
    float halfSizeY = gs_in[0].size * 0.5 / gs_in[0].windowHeight;

    fColor = gs_in[0].color; // gs_in[0] since there's only one input vertex
    gl_Position = position + vec4(-halfSizeX, -halfSizeY, 0.0, 0.0); // 1:bottom-left   
    EmitVertex();   
    gl_Position = position + vec4( halfSizeX, -halfSizeY, 0.0, 0.0); // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-halfSizeX,  halfSizeY, 0.0, 0.0); // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( halfSizeX,  halfSizeY, 0.0, 0.0); // 4:top-right
    EmitVertex();
    EndPrimitive();
}

void main() {    
    build_square(gl_in[0].gl_Position);
}
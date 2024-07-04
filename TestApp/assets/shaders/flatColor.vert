#version 330 core
layout (location = 0) in vec3 aPos;
  
out vec4 oVertexColor;

uniform vec4 uColor;

void main()
{
    oVertexColor = uColor;
    gl_Position = vec4(aPos, 1.0);
}
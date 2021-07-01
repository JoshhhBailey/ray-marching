#version 400 core

layout (location = 0) in vec3 inVert;
layout (location = 1) in vec2 inUV;

out vec2 uv;
uniform vec3 cam_pos;
uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;

void main()
{
    uv = inUV;
    gl_Position = vec4(inVert, 1.0f);
}

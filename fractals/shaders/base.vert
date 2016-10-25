#version 300 es

precision highp float;

layout (location = 0) in vec3 position;
out vec2 vPosition;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    vPosition = vec2(position.x, position.y);
}

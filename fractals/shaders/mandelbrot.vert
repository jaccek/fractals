#version 300 es

precision highp float;

in vec3 iPosition;
in vec2 iCoords;
out vec2 vCoords;

void main()
{
    gl_Position = vec4(iPosition.x, iPosition.y, iPosition.z, 1.0);
    vCoords = iCoords;
}

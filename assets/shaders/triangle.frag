#version 310 es
precision mediump float;
precision highp int;

layout(location = 0) in highp vec3 inColor;

layout(location = 0) out highp vec4 outFragColor;


void main()
{
    outFragColor = vec4(inColor, 1.0);
}

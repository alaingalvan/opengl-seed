#version 410

precision mediump float;
precision highp int;

layout(location = 0) in highp vec3 vColor;

layout(location = 0) out highp vec4 outFragColor;


void main()
{
    outFragColor = vec4(vColor, 1.0);
}

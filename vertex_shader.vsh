#version 450

layout(location = 0) in vec4 inputPosition;
layout(location = 1) in vec4 inputColor;

out vec4 outputColor;

void main(){
    gl_Position = inputPosition;
    outputColor = inputColor;
}
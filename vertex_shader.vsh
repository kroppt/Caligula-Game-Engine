#version 450

layout(location = 0) in vec4 input_position;
layout(location = 1) in vec4 input_color;

out vec4 v_color;

void main(){
    gl_Position = input_position;
    v_color = input_color;
}
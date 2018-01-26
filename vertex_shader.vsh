#version 450

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;

layout(location = 0) in vec3 input_position;
layout(location = 1) in vec4 input_color;
layout(location = 2) in vec2 input_tex_coord;

out vec4 v_color;
out vec2 tex_coord;

void main(){
    //gl_Position = worldToCamera * modelToWorld * vec4(input_position, 1.0f);
    //gl_Position = worldToCamera * vec4(input_position, 1.0f);
    //gl_Position =  modelToWorld * worldToCamera * vec4(input_position, 1.0f);
    gl_Position = modelToWorld * vec4(input_position, 1.0f);
    //gl_Position = vec4(input_position, 1.0f);

    v_color = input_color;
    tex_coord = input_tex_coord;
}
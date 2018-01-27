#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 vp;

layout(location = 0) in vec3 input_position;
layout(location = 1) in vec4 input_color;
layout(location = 2) in vec2 input_tex_coord;
layout(location = 3) in vec3 input_normal;

out vec4 v_color;
out vec2 tex_coord;

void main(){
    gl_Position = vp * model * vec4(input_position, 1.0f);


    v_color = input_color;
    tex_coord = input_tex_coord;
}

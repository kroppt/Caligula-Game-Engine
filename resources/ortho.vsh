#version 450

uniform mat4 model;
uniform vec2 screenSize;

layout(location = 0) in vec3 input_position;
layout(location = 1) in vec4 input_color;
layout(location = 2) in vec2 input_tex_coord;
layout(location = 3) in vec3 input_normal;

out vec4 v_color;
out vec2 tex_coord;

void main(){
    vec4 worldpos = model * vec4(input_position, 1.0);
    vec2 pos = (2.0 * worldpos.xy) / screenSize - vec2(1.0); 
    gl_Position = vec4(pos.xy, 0.0, 1.0 );

    v_color = input_color;
    tex_coord = input_tex_coord;
}

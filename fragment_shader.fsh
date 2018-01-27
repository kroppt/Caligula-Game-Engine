#version 450

in vec4 v_color;
in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D frag_tex;

void main(){
    frag_color = v_color;
 //texture(frag_tex, tex_coord) * v_color;
}
